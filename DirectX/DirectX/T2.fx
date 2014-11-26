struct Vout
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
}

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    // create a VOut struct
    VOut output;

    // set the output values

    output.position = position;
    output.color = color;

    // return the output values
    return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}