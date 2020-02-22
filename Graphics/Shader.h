#ifndef SHADER_HDR
#define SHADER_HDR

#include <string>
#include <array>

namespace gust
{

class Shader
{
public:
    Shader();
    ~Shader();

    void parseShader(const std::string &filePath);
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