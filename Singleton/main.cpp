/*
    In this demo, I have applied the singleton design pattern; which is used to restrict the instantiation of a class to one object.
    This is useful when exactly one object is needed to coordinate actions across the system, for example a Logger or Database class.
    In this particular example I experimented with implementing a persistence manager class specifically for Raylib (not linked with this project),
    but can be tweaked rather easily to fit ones needs. If the current requested resource doesn't exist, the manager will try load and
    store that resource in memory. This means that a so called 'eager initialization' can be executed in the beginning of the program, where
    all the content the application will use during its lifetime is loaded into memory.

    Note: this implementation is not reliable in a multithreaded environment, however it works generally fine in a single-threaded
    environment, though interrupts can be problematic. Also, Singletons are a quick answer to a short term issue, and they are difficult
    to mock for testing when necessary and not scaleable. The dependency injection design pattern is preferable in the vast majority of cases.

    Updated: 2022-07-31
    Author: Jonathan Helsing [github.com/Jonathan-source]
*/


#include <iostream>
#include <string>
#include <unordered_map>


// ----------- Remove this when Raylib is linked -----------------
class Texture {};
class Font {};
class Sound {};

Texture LoadTexture(const char * str) { return Texture(); }
Font LoadFont(const char* str) { return Font(); }
Sound LoadSound(const char* str) { return Sound(); }
//----------------------------------------------------------------


class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    
    static ResourceManager& Instance() {
        static ResourceManager s_instance;
        return s_instance;
    }

    void SetResourcePath(const std::string& fullPath);

    Texture& GetTexture(const std::string& name);

    Font& GetFont(const std::string& name);

    Sound& GetSound(const std::string& name);

private:
    ResourceManager();
    virtual ~ResourceManager() = default;

    std::string m_resourcePath;

    typedef std::unordered_map<std::string, Texture> TextureMap;
    TextureMap m_textures;

    typedef std::unordered_map<std::string, Font> FontMap;
    FontMap m_fonts;

    typedef std::unordered_map<std::string, Sound> SoundMap;
    SoundMap m_sounds;

};


ResourceManager::ResourceManager()
    : m_resourcePath("RESOURCE_PATH_NOT_SET")
{
    std::cout << "[ResourceManager]: constructor invoked\n[ResourceManager]: resource path: " + m_resourcePath << std::endl;
}

void ResourceManager::SetResourcePath(const std::string& fullPath)
{
    m_resourcePath = fullPath;
    std::cout << "[ResourceManager]: new resource path: " + m_resourcePath << std::endl;
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
    TextureMap::iterator it = m_textures.find(name);
    if (it == m_textures.end())
    {
        Texture& texture = m_textures[name];
        texture = LoadTexture(std::string(m_resourcePath + "\\Textures\\" + name).c_str());
        return texture;
    }
    return it->second;
}

Font& ResourceManager::GetFont(const std::string& name)
{
    FontMap::iterator it = m_fonts.find(name);
    if (it == m_fonts.end())
    {
        Font& font = m_fonts[name];
        font = LoadFont(std::string(m_resourcePath + "\\Fonts\\" + name).c_str());
        return font;
    }
    return it->second;
}

Sound& ResourceManager::GetSound(const std::string& name)
{
    SoundMap::iterator it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        Sound& sound = m_sounds[name];
        sound = LoadSound(std::string(m_resourcePath + "\\Sounds\\" + name).c_str());
        return sound;
    }
    return it->second;
}



int main()
{
    {   // Eager initialization.
        // ResourceManager::Instance();
        ResourceManager::Instance().SetResourcePath("..\\Assets\\");
        ResourceManager::Instance().GetTexture("Player.png");
    }

    Texture playerTexture = ResourceManager::Instance().GetTexture("Player.png");

    return 0;
}
