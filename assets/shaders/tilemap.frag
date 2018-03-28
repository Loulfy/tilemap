#version 400 core

precision mediump float;

in vec2 pixelCoord;
in vec2 texCoord;

uniform sampler2D tiles;
uniform sampler2D sprites;

uniform vec2 inverseTileTextureSize;
uniform vec2 inverseSpriteTextureSize;
uniform float tileSize;

out vec4 vColor;

void main(void)
{
    vec4 tile = texture2D(tiles, texCoord);
    if(tile.x == 1.0 && tile.y == 1.0) { discard; }
    vec2 spriteOffset = floor(tile.xy * 256.0) * tileSize;
    vec2 spriteCoord = mod(pixelCoord, tileSize);
    vColor = texture2D(sprites, (spriteOffset + spriteCoord) * inverseSpriteTextureSize);
    //vColor = texture2D(tiles, texCoord);
}