
#include "gd.h"
#include "StringButton.h"

#define FONT_NAME   "Arial"
#define FONT_SIZE   22
#define COLOR       BLUE_3B

USING_NS_CC;

StringButton::StringButton()
: m_pLabel(NULL)
, m_sColor(COLOR)
{
    
}

StringButton::~StringButton()
{
//    GD_SAFE_DELETE(m_pLabel);
}

bool StringButton::init(const char *szString, CCObject *pListener, SEL_ButtonHandler pfnSelector)
{
    if (BaseButton::init(pListener, pfnSelector))
    {
        // Creates label
        m_pLabel = CCLabelTTF::create(szString, FONT_NAME, FONT_SIZE);
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

GD_IMPLEMENT_CREATE_3_ARGS(StringButton, const char*, szString, CCObject*, pListener, SEL_ButtonHandler, pfnSelector);

const char* StringButton::getString() const
{
    return m_pLabel->getString();
}

void StringButton::setString(const char *szString)
{
    m_pLabel->setString(szString);
    
    // Updates content size
    setContentSize(m_pLabel->getContentSize());
}

const char* StringButton::getFontName() const
{
    return m_pLabel->getFontName();
}

void StringButton::setFontName(const char *szFontName)
{
    m_pLabel->setFontName(szFontName);
    
    // Updates content size
    setContentSize(m_pLabel->getContentSize());
}

float StringButton::getFontSize() const
{
    return m_pLabel->getFontSize();
}

void StringButton::setFontSize(float fFontSize)
{
    m_pLabel->setFontSize(fFontSize);
    
    // Updates content size
    setContentSize(m_pLabel->getContentSize());
}

const ccColor3B& StringButton::getColor() const
{
    return m_sColor;
}

void StringButton::setColor(const ccColor3B &sColor)
{
    m_sColor = sColor;
    
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(sColor);
    }
}

void StringButton::setTouchEnabled(bool bTouchEnabled)
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

void StringButton::onSelected(void)
{
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(getReverseColor3B(m_sColor));
    }
}

void StringButton::onUnselected(void)
{
    if (m_bTouchEnabled)
    {
        m_pLabel->setColor(m_sColor);
    }
}
