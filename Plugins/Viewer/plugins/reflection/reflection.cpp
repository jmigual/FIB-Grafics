#include "reflection.h"

const int IMAGE_WIDTH = 1024;
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
    glwidget()->resize(IMAGE_WIDTH, IMAGE_HEIGHT);

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT,
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
    m_pProgram->setUniformValue("colorMap", 0);
    m_pProgram->setUniformValue("modelViewProjectionMatrix",
                                 camera()->projectionMatrix() *
                                 camera()->modelviewMatrix());
    drawPlugin()->drawScene();

    // Get texture
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Pass 2 Draw Scene normal
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    m_pProgram->setUniformValue("factor", (float)1.0);
    drawPlugin()->drawScene();

    // Pass 3 Draw quad using texture
    m_pProgram->release();

    glBindVertexArray(m_VAO_rect);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    m_pProgramS->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

Q_EXPORT_PLUGIN2(reflection, Reflection)   // plugin name, plugin class
