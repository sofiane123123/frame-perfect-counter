#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <string>

using namespace geode::prelude;

int g_jumpCounter = 0;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRun) {
        if (!PlayLayer::init(level, useReplay, dontRun)) return false;

        auto label = CCLabelBMFont::create("Jumps Tracked: 0", "bigFont.fnt");
        label->setPosition({15, 15});
        label->setAnchorPoint({0.0f, 0.0f});
        label->setScale(0.4f);
        label->setOpacity(200);
        label->setTag(5001);
        
        this->addChild(label, 999);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        g_jumpCounter = 0;
        
        if (auto label = static_cast<CCLabelBMFont*>(this->getChildByTag(5001))) {
            label->setString("Jumps Tracked: 0");
        }
    }
};

class $modify(MyPlayer, PlayerObject) {
    void pushButton(PlayerButton btn) {
        PlayerObject::pushButton(btn);
        
        if (auto playLayer = PlayLayer::get()) {
            if (auto label = static_cast<CCLabelBMFont*>(playLayer->getChildByTag(5001))) {
                g_jumpCounter++;
                std::string outputText = "Jumps Tracked: " + std::to_string(g_jumpCounter);
                label->setString(outputText.c_str());
            }
        }
    }
};
