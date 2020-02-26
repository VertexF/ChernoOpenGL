#ifndef SHADER_HDR
#define SHADER_HDR

#include <string>
#include <array>

namespace gust
{

struct ShaderSources 
{
    std::string vertexSource;
    std::string fragementSource;
};

class Shader
{
private:
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

public:
    Shader();
    ~Shader();

    ShaderSources parseShader(const std::string &filePath);
    void openGLSetUp();
private:

    const std::string& makeVertexShader();
    const std::string& makeFragementShader();
    unsigned int compileShader(unsigned int type, const std::string& source);
    void createShader(const std::string& vertexShader, const std::string& fragmentShader);

    std::array<float, 6> _position;
    unsigned int _buffer;
    unsigned int _programID;

    std::string _vertexSource;
    std::string _fragementSource;
};

}

#endif //GAME_HDR