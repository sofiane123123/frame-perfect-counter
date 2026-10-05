#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <string>

using namespace geode::prelude;

CCLabelBMFont* g_framePerfectLabel = nullptr;
int g_localPhysicsStepCounter = 0;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontRun) {
        if (!PlayLayer::init(level, useReplay, dontRun)) return false;

        g_framePerfectLabel = CCLabelBMFont::create("FP Window: Analyzing...", "bigFont.fnt");
        g_framePerfectLabel->setPosition({15, 15});
        g_framePerfectLabel->setAnchorPoint({0.0f, 0.0f});
        g_framePerfectLabel->setScale(0.4f);
        g_framePerfectLabel->setOpacity(200);
        
        this->addChild(g_framePerfectLabel, 999);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        g_localPhysicsStepCounter = 0;
        if (g_framePerfectLabel) {
            g_framePerfectLabel->setString("FP Window: Calculating...");
        }
    }

    void update(float dt) {
        PlayLayer::update(dt);
        // Safely increments each individual internal physics frame calculation tick loop
        g_localPhysicsStepCounter++;
    }
};

class $modify(MyPlayer, PlayerObject) {
    void pushButton(PlayerButton btn) {
        PlayerObject::pushButton(btn);
        
        if (g_framePerfectLabel) {
            std::string outputText = "FP Steps: " + std::to_string(g_localPhysicsStepCounter);
            g_framePerfectLabel->setString(outputText.c_str());
        }
    }
};
