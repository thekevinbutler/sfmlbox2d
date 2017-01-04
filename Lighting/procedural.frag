#version 120
//input textures
uniform sampler2D colourMap;
uniform sampler2D normalMap;

//light properties
uniform vec3 lightPosition = vec3(0.0);
uniform vec3 lightColour = vec3(0.6, 0.6, 0.6);
uniform float lightPower = 0.2;

uniform vec2 resolution = vec2(60.0, 102.0); //set this to size of the sprite to which this shader is applied
uniform bool invertBumpY = true; //some normal maps require inverted Y channel

void main()
{
	//sample our diffuse and normal maps
	vec2 coord = gl_TexCoord[0].xy;
	vec4 diffuseColour = texture2D(colourMap, coord);
	vec3 normalColour = texture2D(normalMap, coord).rgb;
	
	//get normal value from sample
	normalColour.g = invertBumpY ? 1.0 - normalColour.g : normalColour.g;
	vec3 normal = normalize(normalColour * 2.0 - 1.0);
	
	//calculate the light vector
	vec3 lightDir = vec3((lightPosition.xy - gl_FragCoord.xy) / resolution, lightPosition.z);
	
	//calculate the colour intensity based on normal and add specular to pixels facing light
	float colourIntensity = max(dot(normal, normalize(lightDir)), 0.0);
	vec4 specular = vec4(0.0);
	vec4 diffuse = vec4(0.0);
	if(colourIntensity > 0.0)
	{
		//vector half way between light and view direction
		vec3 halfVec = normalize(lightDir + vec3(0.5, 0.5, 0.5)); //fixed 2D view, so view is centred
		
		diffuse = diffuseColour * colourIntensity;		
	}
	
	//add light colour
	diffuseColour.rgb += ((lightColour * lightPower) * colourIntensity);
	diffuseColour.rgb *= diffuseColour.rgb;
	
	//output sum
	gl_FragColor = clamp(specular + diffuse + diffuseColour, 0.0, 1.0);
}





