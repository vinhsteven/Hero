
#include "gd.h"
#include "StringToggle.h"

#define FONT_NAME   "Arial"
#define FONT_SIZE   22
#define COLOR       BLUE_3B

USING_NS_CC;

StringToggle::StringToggle()
: m_szTextOn("")
, m_szTextOff("")
, m_nTagOn(-1)
, m_nTagOff(-1)
, m_bStateOn(false)
, m_pLabel(NULL)
, m_sColor(COLOR)
{
    
}

StringToggle::~StringToggle()
{
    GD_SAFE_DELETE(m_pLabel);
}

bool StringToggle::init(const char *szTextOn, const char *szTextOff, int nTagOn, int nTagOff, bool bStateOn,
                        CCObject *pListener, SEL_ButtonHandler pfnSelector)
{
    if (BaseButton::init(pListener, pfnSelector))
    {
        // Sets text "on"
        m_szTextOn = szTextOn;
        
        // Sets text "off"
        m_szTextOff = szTextOff;
        
        // Sets tag "on"
        m_nTagOn = nTagOn;
        
        // Sets tag "off"
        m_nTagOff = nTagOff;
        
        //
        m_bStateOn = bStateOn;
        
        // Creates label
        m_pLabel = CCLabelTTF::create(bStateOn ? szTextOff : szTextOn, FONT_NAME, FONT_SIZE);
        m_pLabel->setColor(COLOR);
        m_pLabel->setAnchorPoint(CCPointZero);
        
        addChild(m_pLabel);
        
        // Sets color
        m_sColor = COLOR;
        
        // Sets content size
        setContentSize(m_pLabel->getContentSize());
        
        return true;
    }
    
    return false;
}

StringToggle* StringToggle::create(const char *szTextOn, const char *szTextOff, int nTagOn, int nTagOff, bool bStateOn,
                                   CCObject *pListener, SEL_ButtonHandler pfnSelector)
{
    StringToggle *pToggle = GD_NEW(StringToggle);
    
    if (pToggle)
    {
        if (pToggle->init(szTextOn, szTextOff, nTagOn, nTagOff, bStateOn, pListener, pfnSelector))
        {
            pToggle->autorelease();
        }
        else
        {
            GD_DELETE(pToggle);
        }
    }
    
    return pToggle;
}

const char* StringToggle::getFontName() const
{
    return m_pLabel->getFontName();
}

void StringToggle::setFontName(const char *szFontName)
{
    m_pLabel->setFontName(szFontName);
    
    // Updates content size
    setContentSize(m_pLabel->getContentSize());
}

float StringToggle::getFontSize() const
{
    return m_pLabel->getFontSize();
}

void StringToggle::setFontSize(float fFontSize)
{
    m_pLabel->setFontSize(fFontSize);
    
    // Updates content size
    setContentSize(m_pLabel->getContentSize());
}

const ccColor3B& StringToggle::getColor() const
{
    return m_sColor;
}

void StringToggle::setColor(const ccColor3B &sColor)
{
    m_sColor = sColor;
    
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(sColor);
    }
}

void StringToggle::setTouchEnabled(bool bTouchEnabled)
{
    BaseButton::setTouchEnabled(bTouchEnabled);
    
    if (bTouchEnabled)
    {
        if (m_bSelected)
        {
            m_pLabel->setColor(getReverseColor3B(m_sColor));
        }
        else
        {
            m_pLabel->setColor(m_sColor);
        }
    }
    else
    {
        m_pLabel->setColor(GRAY_3B);
    }
}

void StringToggle::onActivate(void)
{
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(m_bStateOn ? m_nTagOff : m_nTagOn);
        
        m_bStateOn = !m_bStateOn;
        
        m_pLabel->setString(m_bStateOn ? m_szTextOff : m_szTextOn);
        
        // Updates content size
        setContentSize(m_pLabel->getContentSize());
    }
}

void StringToggle::onSelected(void)
{
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(getReverseColor3B(m_sColor));
    }
}

void StringToggle::onUnselected(void)
{
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(m_sColor);
    }
}
