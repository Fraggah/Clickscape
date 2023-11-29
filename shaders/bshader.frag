uniform float u_time;
uniform vec2 u_resolution;

void main() {
    // Normalizar las coordenadas del fragmento
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;

    // Calcular las ondas de agua
    float freq = 2.0 + sin(u_time * 0.1);
    float amp = 0.1 + 0.05 * sin(u_time * 0.2);
    float angle = u_time * 0.3;
    vec2 pos = vec2(uv.x + amp * sin(uv.y * freq + angle),
                    uv.y + amp * cos(uv.x * freq + angle));

    // Calcular el color basado en las ondas de agua
    float r = 0.2 + 0.5 * sin(pos.x + u_time);
    float g = 0.1 + 0.5 * cos(pos.y + u_time);
    float b = 0.5 + 0.5 * sin(u_time);
    vec3 color = vec3(r, g, b);

    // Asignar el color al fragmento
    gl_FragColor = vec4(color, 1.0);
}
