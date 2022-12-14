#include "framebuffer.h"

Framebuffer::Framebuffer(int _width, int _height)
    : m_texture(Texture_Rendertarget(_width, _height, TextureData::RGB))
    , m_width(_width)
    ,m_height(_height)
{
    // framebuffer configuration
// -------------------------
    glGenFramebuffers(1, &m_framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
    // create a color attachment texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getID(), 0);

    checkFramebufferComplete();


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::deleteBuffer()
{
    unsigned int textureID = m_texture.getID();

    glDeleteFramebuffers(1, &m_framebufferID);
    glDeleteTextures(1, &textureID);
}

void Framebuffer::createColorTextureAttachement( unsigned int _slot ) {
    glBindFramebuffer( GL_FRAMEBUFFER, m_framebufferID );

    Texture_Rendertarget depthTexure = Texture_Rendertarget( m_width, m_height, TextureData::RGB );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _slot, GL_TEXTURE_2D, depthTexure.getID(), 0 );

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::createDepthTextureAttachement(  ) {
    glBindFramebuffer( GL_FRAMEBUFFER, m_framebufferID );

    Texture_Rendertarget depthTexture = Texture_Rendertarget( m_width, m_height, TextureData::DEPTH );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture.getID(), 0 );

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::createStencilTextureAttachement(  ) {
    glBindFramebuffer( GL_FRAMEBUFFER, m_framebufferID );

    Texture_Rendertarget stencilTexure = Texture_Rendertarget( m_width, m_height, TextureData::STENCIL );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencilTexure.getID(), 0);

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::createDepthRenderbufferAttachement(  ) {
    glBindFramebuffer( GL_FRAMEBUFFER, m_framebufferID );

// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, m_width, m_height ); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo ); // now actually attach it

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::createDepthStencilRenderbufferAttachement(  ) {
    glBindFramebuffer( GL_FRAMEBUFFER, m_framebufferID );

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    unsigned int rbo;
    glGenRenderbuffers( 1, &rbo );
    glBindRenderbuffer( GL_RENDERBUFFER, rbo );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height ); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo ); // now actually attach it

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::checkFramebufferComplete() {
        // check if frambuffer creation is finished
    if (glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}
