#ifndef SKILL_H
#define SKILL_H
#include <string>


class Skill{
private:
    //技能名称
    std::string skillName;

    //冷却
    int CD;

    //技能序号
    int skillID;

public:
    Skill(std::string name = "NONE",int id = 0): skillName(name), CD(0), skillID(id){}
    virtual ~Skill();
    
    //basic accessor and modifiers
    inline std::string getName() const{
        return skillName;
    }

    inline int const getCD() const {
        return CD;
    }

    inline void setCD(int cd)  {
        CD += cd;
    }
    
    inline int const getID() const {
        return skillID;
    }

};

#endif