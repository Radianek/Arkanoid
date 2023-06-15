//
// Created by wawru on 13.06.2023.
//

#ifndef PROJEKT_ICOLLIDABLE_H
#define PROJEKT_ICOLLIDABLE_H


class ICollidable {
    virtual void collide(ICollidable *Other) = 0;
};


#endif //PROJEKT_ICOLLIDABLE_H
