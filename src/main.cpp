#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <string>

using namespace geode::prelude;

CCLabelBMFont* g_framePerfectLabel = nullptr;
int g_jumpCounter = 0;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRun) {
        if (!PlayLayer::init(level, useReplay, dontRun)) return false;

        g_framePerfectLabel = CCLabelBMFont::create("Jumps Tracked: 0", "bigFont.fnt");
        g_framePerfectLabel->setPosition({15, 15});
        g_framePerfectLabel->setAnchorPoint({0.0f, 0.0f});
        g_framePerfectLabel->setScale(0.4f);
        g_framePerfectLabel->setOpacity(200);
        
        this->addChild(g_framePerfectLabel, 999);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        g_jumpCounter = 0;
        if (g_framePerfectLabel) {
            g_framePerfectLabel->setString("Jumps Tracked: 0");
        }
    }
};

class $modify(MyPlayer, PlayerObject) {
    void pushButton(PlayerButton btn) {
        PlayerObject::pushButton(btn);
        
        if (g_framePerfectLabel) {
            g_jumpCounter++;
            std::string outputText = "Jumps Tracked: " + std::to_string(g_jumpCounter);
            g_framePerfectLabel->setString(outputText.c_str());
        }
    }
};
