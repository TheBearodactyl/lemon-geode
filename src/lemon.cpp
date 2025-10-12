#include <Geode/Geode.hpp>
#include <Geode/binding/MenuLayer.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include <Geode/modify/CCLabelTTF.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/TextArea.hpp>

using namespace geode::prelude;

struct LemonLayer: Modify<LemonLayer, MenuLayer> {
    void play_lemo() {
        auto system = FMODAudioEngine::get();
        auto audio = Mod::get()->getResourcesDir() / "lemon.ogg";

        system->playMusic(audio.string(), true, 0.0f, 1);
    }

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        play_lemo();

        return true;
    }
};

struct LemonBMFont: Modify<LemonBMFont, CCLabelBMFont> {
    CCLabelBMFont* create(
        char const* str,
        char const* fnt_file,
        float width,
        CCTextAlignment alignment,
        CCPoint image_offset
    ) {
        return CCLabelBMFont::create(
            "lemon",
            fnt_file,
            width,
            alignment,
            image_offset
        );
    }

    CCLabelBMFont* create(
        char const* str,
        char const* fnt_file,
        float width,
        CCTextAlignment alignment
    ) {
        return CCLabelBMFont::create("lemon", fnt_file, width, alignment);
    }

    CCLabelBMFont* create(char const* str, char const* fnt_file, float width) {
        return CCLabelBMFont::create("lemon", fnt_file, width);
    }

    CCLabelBMFont* create(char const* str, char const* fnt_file) {
        return CCLabelBMFont::create("lemon", fnt_file);
    }

    CCLabelBMFont* create() {
        return CCLabelBMFont::create();
    }

    void setString(char const* new_str) override {
        CCLabelBMFont::setString("lemon");
    }

    void setString(char const* new_str, bool need_update) override {
        CCLabelBMFont::setString("lemon", need_update);
    }

    void setString(unsigned short* str, bool need_update) override {
        CCLabelBMFont::setString(str, need_update);
    }

    char const* getString() override {
        return "lemon";
    }

    bool initWithString(
        char const* str,
        char* const fnt_file,
        float width,
        CCTextAlignment alignment,
        CCPoint image_offset
    ) {
        return CCLabelBMFont::initWithString(
            "lemon",
            fnt_file,
            width,
            alignment,
            image_offset
        );
    }

    void setCString(char const* label) override {
        CCLabelBMFont::setCString("lemon");
    }
};

struct LemonTextArea: Modify<LemonTextArea, TextArea> {
    TextArea* create(
        gd::string str,
        char const* fnt,
        float scale,
        float width,
        cocos2d::CCPoint anchor,
        float line_height,
        bool disable_color
    ) {
        return TextArea::create(
            "lemon",
            fnt,
            scale,
            width,
            anchor,
            line_height,
            disable_color
        );
    }

    /*
    bool init(
        gd::string str,
        char const* fnt,
        float scale,
        float width,
        cocos2d::CCPoint anchor,
        float line_height,
        bool disable_color
    ) {
        return TextArea::init(
            "lemon",
            fnt,
            scale,
            width,
            anchor,
            line_height,
            disable_color
        );
    }
	*/

    void setString(gd::string p0) {
        TextArea::setString("lemon");
    }
};

struct LemonTTF: Modify<LemonTTF, CCLabelTTF> {
    void setString(char const* label) {
        CCLabelTTF::setString("lemon");
    }

    char const* getString() {
        return "lemon";
    }

    CCLabelTTF* create(char const* str, char const* fnt, float font_size) {
        return CCLabelTTF::create("lemon", fnt, font_size);
    }

    CCLabelTTF* create(
        char const* str,
        char const* fnt,
        float font_size,
        CCSize const& dimensions,
        CCTextAlignment halign
    ) {
        return CCLabelTTF::create("lemon", fnt, font_size, dimensions, halign);
    }

    CCLabelTTF* create(
        char const* str,
        char const* fnt,
        float font_size,
        CCSize const& dimensions,
        CCTextAlignment halign,
        CCVerticalTextAlignment valign
    ) {
        return CCLabelTTF::create(
            "lemon",
            fnt,
            font_size,
            dimensions,
            halign,
            valign
        );
    }

    CCLabelTTF* create() {
        this->setString("lemon");

        return CCLabelTTF::create();
    }
};

struct LemonSprite: Modify<LemonSprite, CCSprite> {
    CCSprite* create() {
        return CCSprite::create("lemon.png"_spr);
    }

    CCSprite* create(char const* filename) {
        return CCSprite::create("lemon.png"_spr);
    }

    CCSprite* create(char const* filename, CCRect const& rect) {
        return CCSprite::create("lemon.png"_spr, rect);
    }

    CCSprite* createWithSpriteFrameName(char const* filename) {
        return CCSprite::create("lemon.png"_spr);
    }
};

struct LemonInfoLayer: Modify<LemonInfoLayer, LevelInfoLayer> {
    struct Fields {
        CCSprite* m_lemonbg = nullptr;
    };

    bool init(GJGameLevel* lvl, bool challenge) {
        if (!LevelInfoLayer::init(lvl, challenge)) {
            return false;
        }

        CCSize win_size = CCDirector::get()->getWinSize();

        m_fields->m_lemonbg = CCSprite::create("lemon2.png"_spr);

        if (m_fields->m_lemonbg) {
            m_fields->m_lemonbg->setAnchorPoint({0, 0});
            m_fields->m_lemonbg->setContentWidth(win_size.width);
            m_fields->m_lemonbg->setZOrder(1);

            ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
            m_fields->m_lemonbg->getTexture()->setTexParameters(&params);
            m_fields->m_lemonbg->setTextureRect(
                {0, 0, win_size.width, m_fields->m_lemonbg->getContentHeight()}
            );

            addChild(m_fields->m_lemonbg);
            schedule(schedule_selector(LemonInfoLayer::scroll));
        }

        return true;
    }

    void scroll(float dt) {
        if (!m_fields->m_lemonbg)
            return;

        CCRect texRect = m_fields->m_lemonbg->getTextureRect();
        texRect.origin.x += 25 * dt;

        if (texRect.origin.x >= m_fields->m_lemonbg->getContentWidth()) {
            texRect.origin.x = 0;
        }

        m_fields->m_lemonbg->setTextureRect(texRect);
    }
};
