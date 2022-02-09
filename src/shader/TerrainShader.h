#ifndef TerrainShader_hpp
#define TerrainShader_hpp

#include <stdio.h>
#include <assert.h>
#include "PhongShader.h"


class TerrainShader : public PhongShader
{
public:
    enum {
        DETAILTEX0=0,
        DETAILTEX_COUNT=1
    };

    TerrainShader(const std::string& AssetDirectory);
    virtual ~TerrainShader() {}
    virtual void activate(const BaseCamera& Cam) const;
    virtual void deactivate() const;

    const Texture* detailTex(unsigned int idx) const { assert(idx<DETAILTEX_COUNT); return DetailTex[idx]; }

    void detailTex(unsigned int idx, const Texture* pTex) { assert(idx<DETAILTEX_COUNT); DetailTex[idx] = pTex; }
    void textureScale(float textureScale) { TextureScale = textureScale; }

    void scaling(const Vector& s) { Scaling = s; }
    const Vector& scaling() const { return Scaling; }

private:
    void activateTex(const Texture* pTex, GLint Loc, int slot) const;

    const Texture* DetailTex[DETAILTEX_COUNT];
    Vector Scaling;
    float TextureScale;
    // shader locations
    GLint MixTexLoc;
    GLint DetailTexLoc[DETAILTEX_COUNT];
    GLint ScalingLoc;
    GLint TextureScaleLoc;
};

#endif /* TerrainShader_hpp */
