// libskinning.hlsli
#ifndef LIBSKINNING_HLSLI
#define LIBSKINNING_HLSLI

/*
    Vertex Skinning Library
    Bone blending functions for skeletal animation
    
    (v) 0.1
    (c) agilityseven
*/

#define MAX_BONES 53 // maximum number of bones

/**
 * @brief Applies bone transformation to position/normal with given weight
 *
 * @param[inout] position       Accumulated world position (modified by reference)
 * @param[inout] normal         Accumulated world normal (modified by reference)
 * @param originalPosition      Local-space vertex position
 * @param originalNormal        Local-space vertex normal
 * @param weight                Influence weight (0.0-1.0)
 * @param boneIndex             Index in bones[] array (0-MAX_BONES-1)
 * @param bones                 Array of bone transformation matrices (transposed)
 * 
 * @warning Does NOT normalize resulting normal vector
 */
void blendWeight(inout float4 position, inout float3 normal, float4 originalPosition, float3 originalNormal, float weight, int boneIndex, float4x3 bones[MAX_BONES])
{
    float4x3 boneMatrix = bones[boneIndex];
    position.xyz += mul(originalPosition, boneMatrix) * weight;
    normal += mul(originalNormal, (float3x3) boneMatrix) * weight;
}

/**
 * @brief Blends vertex across multiple bone influences
 * 
 * @param weightCount           Number of active weights (1-4)
 * @param originalPosition      Local-space vertex position
 * @param originalNormal        Local-space vertex normal
 * @param blendWeights          Influence weights (component count >= weightCount)
 * @param blendIndices          Packed bone indices
 * @param[out] normal           Resulting blended world normal
 * @param bones                 Array of bone transformation matrices
 * 
 * @return Blended world position
 * 
 * @warning Fallbacks to original position/normal if weightCount=0
 */
float4 blendWeights(int weightCount, float4 originalPosition, float3 originalNormal, float4 blendWeights, float4 blendIndices, out float3 normal, float4x3 bones[MAX_BONES])
{
    float4 position = float4(0, 0, 0, 1);
    normal = float3(0, 0, 0);

    float totalWeight = 0.0f;
    int remainingWeights = weightCount;

    for (int i = 0; i < remainingWeights; i++)
    {
        float weight = blendWeights[i];
        int boneIndex = int(blendIndices[i] * 255.0f);

        blendWeight(position, normal, originalPosition, originalNormal, weight, boneIndex, bones);
        totalWeight += weight;
    }

    // if there's remaining weight, apply it to the last bone
    if (remainingWeights > 0 && totalWeight < 1.0f)
    {
        float remainingWeight = 1.0f - totalWeight;
        int lastBoneIndex = int(blendIndices[remainingWeights - 1] * 255.0f);

        blendWeight(position, normal, originalPosition, originalNormal, remainingWeight, lastBoneIndex, bones);
    }

    // if no weights are applied, use the original position and normal
    if (remainingWeights == 0)
    {
        position = originalPosition;
        normal = originalNormal;
    }

    return position;
}

#endif // LIBSKINNING_HLSLI