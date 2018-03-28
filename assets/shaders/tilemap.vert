#version 400 core

precision mediump float;

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texture;

out vec2 pixelCoord;
out vec2 texCoord;

uniform vec2 viewOffset;
uniform vec2 viewportSize;
uniform vec2 inverseTileTextureSize;
uniform float inverseTileSize;

void main(void)
{
    pixelCoord = (texture * viewportSize) + viewOffset;
    //pixelCoord = texture * viewportSize;
    texCoord = pixelCoord * inverseTileTextureSize * inverseTileSize;
    gl_Position = vec4(position, 0.0, 1.0);
}