//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include <map>
#include <SFML/Graphics.hpp>

#ifndef RIVERRAID_MAPSHAPE_H
#define RIVERRAID_MAPSHAPE_H

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    //int mapArray(const int* tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif //RIVERRAID_MAPSHAPE_H

