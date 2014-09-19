// Generated by Meshwork HLSL dynamic shader writer


cbuffer Parameters : register(b0)
{
	float4x4 worldMatrix : World;
	float4x4 viewProjectionMatrix : ViewProjection;
	float4 ambientLight;
	float3 viewPosition;
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float materialGloss;
	int activeLightsCount;
	float4 lightsPosIntensity[2];
	float4 lightsColor[2];

};

struct VSInput
{
	float3 pos: POSITION;
	float3 normal: NORMAL;
};

struct SIO
{
	float4 pos: SV_POSITION;
	float4 color: COLOR;
};

struct PSOutput
{
	float4 color: SV_TARGET;
};

SIO VSMain(VSInput input)
{
	SIO output;

	float4 worldPos = mul(worldMatrix, float4(input.pos, 1.0));

	output.pos = mul(viewProjectionMatrix, worldPos);

	float3 normal = normalize(mul(worldMatrix, input.normal));
	float3 viewVector = normalize(viewPosition - worldPos.xyz);
	float3 lightVector;
	float3 lightReflectionVector;
	float lightAttenuation;
	float lightDiffuse;
	float lightSpecular;
	float4 color;
	color = ambientLight * materialAmbient;
	for (int lightIndex = 0; lightIndex < activeLightsCount.x; lightIndex++)
	{
		lightVector = lightsPosIntensity[lightIndex].xyz - worldPos.xyz;
		lightAttenuation = 1 / length(lightVector);
		lightVector *= lightAttenuation;
		lightAttenuation *= lightsPosIntensity[lightIndex].w;
		lightDiffuse = saturate(dot(normal, lightVector)) * lightAttenuation * lightAttenuation;
		lightReflectionVector = normalize(lightVector + viewVector);
		lightSpecular = pow(saturate(dot(normal, lightReflectionVector)), materialGloss);
		color += lightsColor[lightIndex] * (lightDiffuse * materialDiffuse + lightSpecular * materialSpecular);
	}

	output.color = color;

	return output;
}

PSOutput PSMain(SIO input)
{
	PSOutput output;

	

	output.color = input.color;

	return output;
}