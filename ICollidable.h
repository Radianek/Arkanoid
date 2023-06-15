//
// Created by wawru on 13.06.2023.
//

#ifndef PROJEKT_ICOLLIDABLE_H
#define PROJEKT_ICOLLIDABLE_H
#include <SFML/Graphics.hpp>

class ICollidable {
public:
    virtual ~ICollidable() = default;

    virtual sf::FloatRect get_bounds() const = 0;


    virtual bool check_collision(const ICollidable& other) const {

        return get_bounds().intersects(other.get_bounds());
    }bool check_collision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
        return rect1.intersects(rect2);
    }
    bool check_collision(const ICollidable& object1, const ICollidable& object2) {
        sf::FloatRect bounds1 = object1.get_bounds();
        sf::FloatRect bounds2 = object2.get_bounds();

        return bounds1.intersects(bounds2);
    }


};


#endif //PROJEKT_ICOLLIDABLE_H
