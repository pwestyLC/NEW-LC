#include "libskinning.hlsli"

// vertex shader constants
float4x4 worldViewProj : register(c0);
float4 lightDir : register(c4);
float4 lightColor : register(c5);
float4 ambientColor : register(c6);
float4 cameraPosition : register(c8);
float4x3 bones[MAX_BONES] : register(c21);
float4 time : register(c17);

// shader defined specular constants
static const float4 specularColor = float4(0.9, 0.9, 0.9, 1.0);
static const float specularPower = 32.0;

struct VS_INPUT
{
    float4 position : POSITION0;
    float3 normal : NORMAL;
    float4 blendWeights : BLENDWEIGHT;
    float4 blendIndices : BLENDINDICES;
    float2 texCoord0 : TEXCOORD0;
};

// we extend the output so that the pixel shader gets the world position and base normal
struct VS_OUTPUT
{
    float4 position : POSITION;   // clip-space position
    float2 texCoord0 : TEXCOORD0;   // texture coordinates
    float3 worldPos : TEXCOORD1;    // world space position
    float3 worldNormal : TEXCOORD2; // skinned (base) world-space normal
};

VS_OUTPUT vs_main(VS_INPUT input)
{
    VS_OUTPUT output;
    float3 normal;
    
    // apply skinning using the blendWeights function from the library
    float4 skinnedPos = blendWeights(4, input.position, input.normal, input.blendWeights, input.blendIndices, normal, bones);

    // normalize the skinned normal
    normal = normalize(normal);

    // transform to clip space
    output.position = mul(skinnedPos, worldViewProj);

    // pass through texture coordinates
    output.texCoord0 = input.texCoord0;
    
    // pass along the skinned world position and normal for per-pixel lighting
    output.worldPos = skinnedPos.xyz;
    output.worldNormal = normal;

    return output;
}