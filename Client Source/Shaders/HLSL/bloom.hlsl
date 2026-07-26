/*
    Bloom Effect Shader

    Vertex shader prepares sample offsets, while the pixel
    shader blends a single texture sampled four times.
    
    (v) 0.2
    (c) agilityseven
*/

// vertex shader constants
float4x4 worldViewProj : register(c0);    // projection matrix
float4 texOffset[4] : register(c10);      // texture coordinate offsets

// pixel shader constants
float4 multFactor0 : register(c0);
float4 multFactor1 : register(c1);
float4 multFactor2 : register(c2);
float4 multFactor3 : register(c3);

// texture sampler
sampler2D tex : register(s0);

struct VS_OUTPUT
{
    float4 position : POSITION;
    float4 texCoord0 : TEXCOORD0;
    float4 texCoord1 : TEXCOORD1;
    float4 texCoord2 : TEXCOORD2;
    float4 texCoord3 : TEXCOORD3;
};

VS_OUTPUT vs_main(
    float4 position : POSITION,
    float4 texCoord2 : TEXCOORD2)
{
    VS_OUTPUT output;
    
    // transform the vertex position using the projection matrix
    output.position = mul(position, worldViewProj);
    
    // generate four offset texture coordinates
    output.texCoord0 = texCoord2 + texOffset[0];
    output.texCoord1 = texCoord2 + texOffset[1];
    output.texCoord2 = texCoord2 + texOffset[2];
    output.texCoord3 = texCoord2 + texOffset[3];
    
    return output;
}

float4 ps_main (
    float2 texCoord0 : TEXCOORD0,
    float2 texCoord1 : TEXCOORD1,
    float2 texCoord2 : TEXCOORD2,
    float2 texCoord3 : TEXCOORD3) : COLOR0
{    
    float4 sample0 = tex2D(tex, texCoord0);
    float4 sample1 = tex2D(tex, texCoord1);
    float4 sample2 = tex2D(tex, texCoord2);
    float4 sample3 = tex2D(tex, texCoord3);
    
    // blend samples using multiplication factors (only rgb channels)
    float3 blended = float3(0.0, 0.0, 0.0);

    blended += sample0.rgb * multFactor0.rgb;
    blended += sample1.rgb * multFactor1.rgb;
    blended += sample2.rgb * multFactor2.rgb;
    blended += sample3.rgb * multFactor3.rgb;
 
    return float4(blended, sample0.a);
}