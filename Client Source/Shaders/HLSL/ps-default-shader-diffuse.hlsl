sampler s0 : register(s0); // sampler for the diffuse texture

struct PS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD0;
    float4 diffuseColor : COLOR;
};

// set via shader constant table
float power = 1.0;

float4 ps_main(PS_INPUT input) : COLOR
{
    // sample the diffuse texture
    float4 diffuseTexture = tex2D(s0, input.uv);

    // calculate (diffuseColor.rgb + ambientColor.rgb) * diffuseTexture.rgb
    // since we don't have ambient color as separate input, we assume it is embedded in diffuseColor
    // multiplication by 2 and saturation implemented by min(1, x*2)
    float3 outputColorRGB = min(1.0, diffuseTexture.rgb * input.diffuseColor.rgb * power);

    // calculate diffuseTexture.a * diffuseColor.a, clamped to [0,1] by saturation
    float outputAlpha = saturate(diffuseTexture.a * input.diffuseColor.a);

    // combine the color and alpha
    float4 outputColor = float4(outputColorRGB, outputAlpha);

    return outputColor;
}