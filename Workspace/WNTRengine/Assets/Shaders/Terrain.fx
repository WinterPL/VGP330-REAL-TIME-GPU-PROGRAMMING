// Description: Simple shader that does transform.

cbuffer TransformBuffer : register(b0)
{
    matrix world;
	matrix wvp;
	matrix lwvp;
    float3 viewPosition;
}

cbuffer LightBuffer : register(b1)
{
    float4 lightAmbient;
    float4 lightDiffuse;
    float4 lightSpecular;
    float3 lightDirection;
}

cbuffer MeterialBuffer : register(b2)
{
    float4 materialAmbient;
    float4 materialDiffuse;
    float4 materialSpecular;
    float4 materialEmissive;
    float materialPower;
}

cbuffer SettingBuffer : register(b3)
{
    bool useShadowMap;
    float depthBias;
}


Texture2D diffuseMap : register(t0);
Texture2D specMap : register(t1);
Texture2D shadowMap : register(t2);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
    float3 worldNormal : NORMAL;
    float3 dirToLight : TEXCOORD0;
    float3 dirToView : TEXCOORD1;
	float2 texCoord : TEXCOORD2;
    float4 lightNDCPosition : TEXCOORD3;
    float4 worldPosition : TEXCOORD4;
};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	
    matrix toWorld = world;
    matrix toNDC = wvp;
    float3 localPosition = input.position;

	output.position = mul(float4(localPosition, 1.0f), toNDC);
    output.worldNormal = mul(input.normal, (float3x3) toWorld);
    output.dirToLight = -lightDirection;
    output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), toWorld).xyz);
	output.texCoord = input.texCoord;
    output.lightNDCPosition = mul(float4(localPosition, 1.0f), lwvp);
    output.worldPosition = mul(float4(localPosition, 1.0f), toWorld);

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 n = normalize(input.worldNormal);
    float3 light = normalize(input.dirToLight);
    float3 view = normalize(input.dirToView);
   
    //ambient color
    float4 ambient = lightAmbient*materialAmbient;
    //diffuse color
    float d = saturate(dot(light, n));
    float4 diffuse = d * lightDiffuse * materialDiffuse;
    //specular
    float3 r = reflect(-light, n);
    float base = saturate(dot(r, view));
    float s = pow(base, materialPower);
    float4 specular = s * lightSpecular * materialSpecular;

    //emissive color
    float4 emissive = materialEmissive;

    //get color from texture
    float4 diffuseMapColor =diffuseMap.Sample(textureSampler, input.texCoord);
    float4 specMapColor = specMap.Sample(textureSampler, input.texCoord);
    float4 colorToUse = diffuseMapColor;
    if (input.worldPosition.y > 15.0f)
    {
        colorToUse = specMapColor;
    }
    else{
        float t = (input.worldPosition.y - 10.0f) / 5.0f;
        colorToUse = lerp(diffuseMapColor, specMapColor, t);
    }
    
    //combine colors for final result
    float4 finalColor = (ambient + diffuse + emissive) * colorToUse + specular;
    if (useShadowMap)
    {
        float actualDepth = 1.0f - (input.lightNDCPosition.z / input.lightNDCPosition.w);
        float2 shadowUV = input.lightNDCPosition.xy / input.lightNDCPosition.w;
        float u = (shadowUV.x + 1.0f) * 0.5f;
        float v = 1.0f - (shadowUV.y + 1.0f) * 0.5f;
        if (saturate(u) == u && saturate(v) == v)
        {
            float4 savedColor = shadowMap.Sample(textureSampler, float2(u, v));
            float savedDepth = savedColor.r;
            if (savedDepth > actualDepth + depthBias) 
            {
                finalColor = (ambient + materialEmissive) * colorToUse;
            }
        }
    }
    return finalColor;
	//return colorToUse;
}