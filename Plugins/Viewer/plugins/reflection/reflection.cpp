#include "reflection.h"

const int IMAGE_WIDTH = 700;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

int printOglError(const char file[], int line, const char func[])
{
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR) {
        printf("glError in file %s @ line %d: %s function: %s\n",
               file, line, gluErrorString(glErr), func);
        retCode = 1;
    }
    return retCode;
}

void Reflection::onPluginLoad()
{
    // Resize to power-of-two viewport
    //glwidget()->resize(IMAGE_WIDTH, IMAGE_HEIGHT);

    // Carregar shader, compile & link
    m_pVs = new QGLShader(QGLShader::Vertex, this);
    m_pVs->compileSourceFile(":/reflection.vert");

    m_pFs = new QGLShader(QGLShader::Fragment, this);
    m_pFs->compileSourceFile(":/reflection.frag");

    m_pProgram = new QGLShaderProgram(this);
    m_pProgram->addShader(m_pVs);
    m_pProgram->addShader(m_pFs);
    m_pProgram->link();


    // Setup texture
    glActiveTexture(GL_TEXTURE0);
    glGenTextures( 1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, glwidget()->width(), glwidget()->height(), 0, GL_RGB, GL_FLOAT,
                 NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create & bind empty VAO
    glGenVertexArrays(1, &m_VAO_rect);
    glBindVertexArray(m_VAO_rect);

    // Create VBO with (x,y,z) coordinates
    float coords[] = { -1, -1, -1,
                       1,  -1, -1,
                       -1,  -1,  1,
                       1,  -1,  1 };

    GLuint VBO_coords;
    glGenBuffers(1, &VBO_coords);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}


bool Reflection::paintGL()
{
    // Pass 1. Draw scene reversed and store it to the texture
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    m_pProgram->bind();
    m_pProgram->setUniformValue("factor", (float)-1.0);
    m_pProgram->setUniformValue("texture", false);
    m_pProgram->setUniformValue("colorMap", 0);
    m_pProgram->setUniformValue("SIZE", QVector2D(glwidget()->width(), glwidget()->height()));
    
    Box b = scene()->boundingBox();
    m_pProgram->setUniformValue("radius", b.radius());
    m_pProgram->setUniformValue("boundingMin", b.min());
    m_pProgram->setUniformValue("boundingMax", b.max());
    
    m_pProgram->setUniformValue("modelViewProjectionMatrix",
                                camera()->projectionMatrix() *
                                camera()->modelviewMatrix());
    m_pProgram->setUniformValue("modelViewMatrix", camera()->modelviewMatrix());
    m_pProgram->setUniformValue("normalMatrix", camera()->modelviewMatrix().normalMatrix());

    // Ligth specs
    m_pProgram->setUniformValue("lightAmbient", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightDiffuse", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightSpecular", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightPosition", QVector4D(100., 100., 100., 1.));

    m_pProgram->setUniformValue("matAmbient", QVector4D(.5, .4, .0, 1.));
    m_pProgram->setUniformValue("matDiffuse", QVector4D(.5, .4, .0, 1.));
    m_pProgram->setUniformValue("matSpecular", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("matShininess", (float) 30.);

    drawPlugin()->drawScene();

    // Get texture
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, glwidget()->width(), glwidget()->height());
    glGenerateMipmap(GL_TEXTURE_2D);

    // Pass 2 Draw Scene normal
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    m_pProgram->setUniformValue("factor", (float)1.0);

    
    drawPlugin()->drawScene();

    // Pass 3 Draw quad using texture
    m_pProgram->setUniformValue("texture", true);
    glBindVertexArray(m_VAO_rect);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    m_pProgram->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

Q_EXPORT_PLUGIN2(reflection, Reflection)   // plugin name, plugin class
