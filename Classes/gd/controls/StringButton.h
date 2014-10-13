
#ifndef _GD_CONTROLS_STRING_BUTTON_H_
#define _GD_CONTROLS_STRING_BUTTON_H_

#include "BaseButton.h"

class StringButton : public BaseButton
{
public:
    
    StringButton();
    
    virtual ~StringButton();
    
    virtual bool init(const char *szString, CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
    static StringButton* create(const char *szString, CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
    /** Gets string */
    virtual const char* getString() const;
    
    /** Sets string */
    virtual void setString(const char *szString);
    
    /** Gets font name */
    virtual const char* getFontName() const;
    
    /** Sets font name */
    virtual void setFontName(const char *szFontName);
    
    /** Gets font size */
    virtual float getFontSize() const;
    
    /** Sets font size */
    virtual void setFontSize(float fFontSize);
    
    /** Gets color */
    virtual const ccColor3B& getColor() const;
    
    /** Sets color */
    virtual void setColor(const ccColor3B &sColor);
    
    /** Sets touch enabled or not */
    virtual void setTouchEnabled(bool bTouchEnabled);
    
protected:
    
    /** On selected */
    virtual void onSelected(void);
    
    /** On unselected */
    virtual void onUnselected(void);
    
protected:
    
    // The label to display text
    CCLabelTTF *m_pLabel;
    
    // The text color
    ccColor3B m_sColor;
};

#endif  // _GD_CONTROLS_STRING_BUTTON_H_
