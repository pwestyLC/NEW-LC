#ifndef LIGHTING_HLSLI
#define LIGHTING_HLSLI

// lighting functions

// Diffuse Lighting (Lambertian)
float3 CalculateDiffuseLighting(float3 normal, float3 lightDirection, float3 lightColor, float3 albedo)
{
    // ensure normal and lightDir are normalized for accurate dot product
    normal = normalize(normal);
    lightDirection = normalize(lightDirection);

    float NdotL = saturate(dot(normal, lightDirection));
    return lightColor * albedo * NdotL;
}

// Ambient Lighting
float3 CalculateAmbientLighting(float3 ambientColor, float3 albedo)
{
    return ambientColor * albedo;
}

// Specular Lighting (Blinn-Phong)
float3 CalculateBlinnPhongLighting(float3 normal, float3 lightDirection, float3 viewDirection, float3 lightColor, float3 specularColor, float shininess)
{
    // ensure normal, lightDir, and viewDir are normalized
    normal = normalize(normal);
    lightDirection = normalize(lightDirection);
    viewDirection = normalize(viewDirection);

    float3 halfVector = normalize(lightDirection + viewDirection);
    float NdotH = saturate(dot(normal, halfVector));
    float specularFactor = pow(NdotH, shininess);
    return lightColor * specularColor * specularFactor;
}

// Specular Lighting (Phong) - alternative to Blinn-Phong
float3 CalculatePhongSpecularLighting(float3 normal, float3 lightDirection, float3 viewDirection, float3 lightColor, float3 specularColor, float shininess)
{
    // ensure normal, lightDir, and viewDir are normalized
    normal = normalize(normal);
    lightDirection = normalize(lightDirection);
    viewDirection = normalize(viewDirection);

    float3 reflectedLight = reflect(-lightDirection, normal); // reflect light direction around normal
    float RdotV = saturate(dot(reflectedLight, viewDirection));
    float specularFactor = pow(RdotV, shininess);
    return lightColor * specularColor * specularFactor;
}

// Combined Lighting (Diffuse + Ambient + Specular - Blinn-Phong)
float3 CalculateBlinnPhongLightingCombined(float3 normal, float3 lightDirection, float3 viewDirection, float3 lightColor, float3 ambientColor, float3 albedo, float3 specularColor, float shininess)
{
    float3 diffuse = CalculateDiffuseLighting(normal, lightDirection, lightColor, albedo);
    float3 ambient = CalculateAmbientLighting(ambientColor, albedo);
    float3 specular = CalculateBlinnPhongLighting(normal, lightDirection, viewDirection, lightColor, specularColor, shininess);
    return diffuse + ambient + specular; // additive lighting
}

// Combined Lighting (Diffuse + Ambient + Specular - Phong) - alternative to Blinn-Phong combined
float3 CalculatePhongLightingCombined(float3 normal, float3 lightDirection, float3 viewDirection, float3 lightColor, float3 ambientColor, float3 albedo, float3 specularColor, float shininess)
{
    float3 diffuse = CalculateDiffuseLighting(normal, lightDirection, lightColor, albedo);
    float3 ambient = CalculateAmbientLighting(ambientColor, albedo);
    float3 specular = CalculatePhongSpecularLighting(normal, lightDirection, viewDirection, lightColor, specularColor, shininess);
    return diffuse + ambient + specular; // additive lighting
}

// light types

// Point Light - for point light source
float3 CalculatePointLightDiffuse(float3 worldPosition, float3 normal, float3 lightPosition, float3 lightColor, float3 albedo, float lightAttenuation)
{
    float3 lightDirection = lightPosition - worldPosition; // direction from point to vertex
    float distanceToLight = length(lightDirection);
    lightDirection /= distanceToLight; // normalize light direction

    float attenuation = 1.0f / (1.0f + lightAttenuation * distanceToLight * distanceToLight); // ex quadratic attenuation

    float3 diffuse = CalculateDiffuseLighting(normal, lightDirection, lightColor, albedo);
    return diffuse * attenuation;
}

float3 CalculatePointLightBlinnPhong(float3 worldPosition, float3 normal, float3 lightPosition, float3 viewDirection, float3 lightColor, float3 specularColor, float shininess, float3 albedo, float ambientColor, float lightAttenuation)
{
    float3 lightDirection = lightPosition - worldPosition; // direction from point to vertex
    float distanceToLight = length(lightDirection);
    lightDirection /= distanceToLight; // normalize light direction

    float attenuation = 1.0f / (1.0f + lightAttenuation * distanceToLight * distanceToLight); // ex quadratic attenuation

    float3 diffuse = CalculatePointLightDiffuse(worldPosition, normal, lightPosition, lightColor, albedo, lightAttenuation);
    float3 ambient = CalculateAmbientLighting(ambientColor, albedo);
    float3 specular = CalculateBlinnPhongLighting(normal, lightDirection, viewDirection, lightColor, specularColor, shininess); // Blinn-Phong specular

    return (diffuse + specular + ambient) * attenuation;
}

// Spot Light - for spot light source (inherits from point light)
float3 CalculateSpotLightDiffuse(float3 worldPosition, float3 normal, float3 lightPosition, float3 lightDirectionSpot, float3 lightColor, float3 albedo, float lightAttenuation, float spotCutoff, float spotExponent)
{
    float3 pointLightDiffuse = CalculatePointLightDiffuse(worldPosition, normal, lightPosition, lightColor, albedo, lightAttenuation);

    float spotFactor = dot(-normalize(lightDirectionSpot), normalize(lightPosition - worldPosition)); // cosine of angle between spot direction and light-to-vertex direction
    spotFactor = saturate((spotFactor - spotCutoff) / (1.0f - spotCutoff)); // smooth step for spot edge
    spotFactor = pow(spotFactor, spotExponent); // sharpen spot light

    return pointLightDiffuse * spotFactor;
}

float3 CalculateSpotLightBlinnPhong(float3 worldPosition, float3 normal, float3 lightPosition, float3 lightDirectionSpot, float3 viewDirection, float3 lightColor, float3 specularColor, float shininess, float3 albedo, float ambientColor, float lightAttenuation, float spotCutoff, float spotExponent)
{
    float3 pointLightBlinnPhong = CalculatePointLightBlinnPhong(worldPosition, normal, lightPosition, viewDirection, lightColor, specularColor, shininess, albedo, ambientColor, lightAttenuation);

    float spotFactor = dot(-normalize(lightDirectionSpot), normalize(lightPosition - worldPosition)); // cosine of angle between spot direction and light-to-vertex direction
    spotFactor = saturate((spotFactor - spotCutoff) / (1.0f - spotCutoff)); // smooth step for spot edge
    spotFactor = pow(spotFactor, spotExponent); // sharpen spot light

    return pointLightBlinnPhong * spotFactor;
}

// advanced effects

// Alternative Diffuse Model (Oren-Nayar) - for rougher surfaces
float3 CalculateOrenNayarDiffuse(float3 normal, float3 lightDirection, float3 lightColor, float3 albedo, float roughness)
{
    // roughness should be in [0, 1] range.
    roughness = saturate(roughness);
    float roughnessSq = roughness * roughness;

    float sigmaSq = roughnessSq; // simplified roughness parameter.
    float A = 1.0f - 0.5f * (sigmaSq / (sigmaSq + 0.33f));
    float B = 0.45f * (sigmaSq / (sigmaSq + 0.09f));

    float NdotL = saturate(dot(normal, lightDirection));
    float VdotN = saturate(dot(viewDirection, normal)); // need viewDirection passed to function.
    float VdotL = saturate(dot(viewDirection, lightDirection));

    float alpha = max(0.0f, acos(NdotL)); // angle between normal and light direction
    float beta = max(0.0f, acos(VdotN));  // angle between normal and view direction

    float gamma = 0.0f;
    if (NdotL > 0.0f && VdotN > 0.0f)
    {
        gamma = acos(saturate(VdotL / (sin(alpha) * sin(beta)))); // angle between projected light and view directions
    }

    float diffuseFactor = NdotL * (A + B * max(0.0f, cos(gamma)) * sin(alpha) * tan(beta)); // Oren-Nayar formula

    return lightColor * albedo * diffuseFactor;
}

#endif // LIGHTING_HLSLI