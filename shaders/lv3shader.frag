#version 330 core

uniform float time;
uniform vec2 resolution;

out vec4 FragColor;

void main()
{
    // Normaliza las coordenadas de fragmento
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    // Crea múltiples efectos de onda basados en el tiempo y la posición
    float wave1 = sin(uv.y * 10.0 + time) * 0.1 + sin(uv.x * 10.0 + time) * 0.1;
    float wave2 = sin(uv.y * 20.0 + time) * 0.05 + sin(uv.x * 20.0 + time) * 0.05;
    float wave3 = sin(uv.y * 30.0 + time) * 0.025 + sin(uv.x * 30.0 + time) * 0.025;

    // Crea múltiples efectos de parpadeo basados en el tiempo
    float blink1 = sin(time * 10.0) * 0.5 + 0.5;
    float blink2 = sin(time * 20.0) * 0.25 + 0.75;
    float blink3 = sin(time * 30.0) * 0.125 + 0.875;

    // Combina los efectos de onda y parpadeo para obtener un color
    vec3 color = vec3(blink1 * wave1 * 2.0, blink2 * wave2 * 2.0, blink3 * wave3 * 2.0);

    // Asigna el color al fragmento
    FragColor = vec4(color, 1.0);
}

//Decidí implemetar shaders de fondos, ya que es algo que me interesa y estuve indagando bastante
//Intenté implementar un filtro que capture la salida de SFML y aplicarle al output un efecto CRT
//pero fracasé miserablemente...