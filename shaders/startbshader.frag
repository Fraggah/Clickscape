#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    vec3 color = vec3(0.0);

    float frequency = 10.0;
    float amplitude = 0.03;
    float speed = 1.0;

    for (int i = 0; i < 3; ++i) {
        float wave = sin(uv.y * frequency + u_time * speed) * amplitude;
        color[i] = wave;
        frequency += 5.0;
        amplitude -= 0.02;
        speed += 0.5;
    }

    gl_FragColor = vec4(color, 1.0);
}
