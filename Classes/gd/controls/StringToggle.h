
#ifndef _GD_CONTROLS_STRING_TOGGLE_H_
#define _GD_CONTROLS_STRING_TOGGLE_H_

#include "BaseButton.h"

class StringToggle : public BaseButton
{
public:
    
    StringToggle();
    
    virtual ~StringToggle();
    
    virtual bool init(const char *szTextOn, const char *szTextOff, int nTagOn, int nTagOff, bool bStateOn,
                      CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
    static StringToggle* create(const char *szTextOn, const char *szTextOff, int nTagOn, int nTagOff, bool bStateOn,
                                CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
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
    
    /** On activate */
    virtual void onActivate(void);
    
    /** On selected */
    virtual void onSelected(void);
    
    /** On unselected */
    virtual void onUnselected(void);
    
protected:
    
    // The text "on"
    const char *m_szTextOn;
    
    // The text "off"
    const char *m_szTextOff;
    
    // The tag "on"
    int m_nTagOn;
    
    // The tag "off"
    int m_nTagOff;
    
    // The label to display text
    CCLabelTTF *m_pLabel;
    
    // The text color
    ccColor3B m_sColor;
    
    // Is state on?
    bool m_bStateOn;
};

#endif  // _GD_CONTROLS_STRING_TOGGLE_H_
