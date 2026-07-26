sampler Sam : register(s0);

// time input from constant register c17.x
float Time : register(c17);

float4 ps_main(float2 TexCoord : TEXCOORD0) : COLOR
{
    float4 originalColor = tex2D(Sam, TexCoord);

    // define semi-transparent gray mesh color
    float4 meshColor = float4(0.5, 0.5, 0.5, 0.5); // gray mesh color with opacity

    float wobbleSpeed = 2.0;
    float wobbleAmount = 0.02;
    float gridDensity = 8.0;
    float scanSpeed = 3.0;
    float loopDuration = 4.0;

    // calculate looped time
    float loopTime = frac(Time / loopDuration);

    // distort texture coordinates
    float2 distortedTexCoord = TexCoord;
    distortedTexCoord.x += cos(Time * wobbleSpeed + TexCoord.y * gridDensity) * wobbleAmount;
    distortedTexCoord.y += sin(Time * wobbleSpeed + TexCoord.x * gridDensity) * wobbleAmount;

    // create grid lines
    float gridX = sin(distortedTexCoord.x * gridDensity * 3.14159);
    float gridY = sin(distortedTexCoord.y * gridDensity * 3.14159);
    float grid = gridX * gridY;

    // looping linear gradient
    float scanPosition = loopTime * scanSpeed;
	
    // linear gradient from top (TexCoord.y = 0) to bottom (TexCoord.y = 1) based on scanPosition
    float verticalGradient = saturate(1.0 - abs(TexCoord.y - scanPosition) * 5.0); // adjust 5.0 for gradient sharpness


    // combine gradient with grid (simplified opacity)
    float opacityGradient = verticalGradient * saturate(1.0 - abs(grid) * 1.5);


    // create grid color with gradient opacity
    float4 gridColor = float4(meshColor.rgb, opacityGradient);

    // blend with original color
    float4 scannedColor = lerp(originalColor, gridColor, opacityGradient);

    return scannedColor;
}