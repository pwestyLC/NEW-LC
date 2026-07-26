// include the skinning library
#include "libskinning.hlsli"

// vertex shader constants
float4x4 worldViewProj : register(c0);
float4 lightDir : register(c4);
float4 lightColor : register(c5);
float4 ambientColor : register(c6);
float4 cameraPosition : register(c8);
float4x3 bones[MAX_BONES] : register(c21);
float4 time : register(c17);
// FIXME: constant table is fucking so gross I cant believe why this doesnt work properly when 2 or more constants are defined XD
//int weightCount;

// Shader defined specular constants
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

struct VS_OUTPUT
{
    float4 position : POSITION;
    float2 texCoord0 : TEXCOORD0;
    float4 color : COLOR;
};

void diffuse(inout VS_OUTPUT output, float3 normal)
{
    // normal dot light
    float NdotL = dot(normal, lightDir.xyz);

    // clamp NdotL between 0 and 1
    NdotL = clamp(NdotL, 0.0f, 1.0f);

    // calculate diffuse lighting
    float3 diffuse = lightColor * NdotL;

    // add ambient light
    float3 finalColor = diffuse + ambientColor.rgb;

    // set output color
    output.color = float4(finalColor, 1.0f);

    // clamp output color to 1.0f
    output.color = min(output.color, 1.0f);
}

void specularDiffuse(inout VS_OUTPUT output, float3 worldPosition, float3 normal)
{
    // normalize vectors (essential for correct lighting calculations)
    float3 lightDirectionNormalized = normalize(lightDir.xyz); // light direction (L)
    float3 viewDirectionNormalized  = normalize(cameraPosition.xyz - worldPosition); // view direction (V) from surface to camera
    float3 normalNormalized       = normalize(normal); // surface normal (N)

    // diffuse calculation (lambertian)
    float NdotL = max(0.0f, dot(normalNormalized, lightDirectionNormalized)); // cosine of angle between N and L (clamped to 0+)
    float3 diffuseComponent = lightColor.rgb * NdotL; // diffuse color contribution

    // specular calculation (blinn-phong)
    float3 halfVector = normalize(lightDirectionNormalized + viewDirectionNormalized); // half-vector (H)
    float NdotH = max(0.0f, dot(normalNormalized, halfVector)); // cosine of angle between N and H (clamped to 0+)
    float specularIntensity = pow(NdotH, specularPower); // specular intensity based on shininess
    float3 specularComponent = specularColor.rgb * specularIntensity; // specular color contribution

    // ambient calculation (simple constant ambient)
    float3 ambientComponent = ambientColor.rgb; // ambient color contribution

    // combine lighting components
    float3 finalColor = diffuseComponent + specularComponent + lightColor;

    // set output color
    output.color = float4(finalColor, 1.0f);

    // clamp output color (saturate to [0, 1] range)
    output.color = min(output.color, 1.0f); // or saturate(float4(finalColor, 1.0f));
}

VS_OUTPUT vs_main(VS_INPUT input)
{
    VS_OUTPUT output;
    float3 normal;
    
    // use the blendWeights function from the library, passing individual components from VS_INPUT
    float4 position = blendWeights(4, input.position, input.normal, input.blendWeights, input.blendIndices, normal, bones);

    // normalize - not used atm
    normal = normalize(normal);

    // transform position
    output.position = mul(position, worldViewProj);

    // pass through texture coordinates
    output.texCoord0 = input.texCoord0;

    // diffuse texture
    //diffuse(output, normal);

    // specular and diffuse lighting calculation
    //specularDiffuse(output, position.xyz, normal);

    // lighting selection based on time (using floor for integer part of time)
    //if (fmod(floor(time.x), 5.0) == 0.0) // even seconds - diffuse
    //{
    //    diffuse(output, normal);
    //}
    //else // Odd seconds - SpecularDiffuse
    //{
    //    specularDiffuse(output, position.xyz, normal);
    //}
    return output;
}