
#ifndef _I_CHARACTER_EVENT_LISTENER_H_
#define _I_CHARACTER_EVENT_LISTENER_H_

class Character;

class ICharacterEventListener
{
public:
    
    /** On character position changed */
    virtual void onCharacterPositionChanged(Character *pCharacter) {}
};

// Null Object
extern ICharacterEventListener theNullCharacterEventListener;

#endif // _I_CHARACTER_EVENT_LISTENER_H_
