#include <Geode/Geode.hpp>
#include <Geode/modify/CCSpriteFrameCache.hpp>
#include <Geode/modify/CCTextureCache.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static CCTexture2D* g_lemontex = nullptr;

struct LemonTextureCache: Modify<LemonTextureCache, CCTextureCache> {
	CCTexture2D* addImage(const char* path, bool p1) {
		auto orig_tex = CCTextureCache::addImage(path, p1);

		if (!g_lemontex) {
			g_lemontex = CCTextureCache::addImage("lemon.png"_spr, false);
		}

		if (g_lemontex && orig_tex) {
			return g_lemontex;
		}

		return orig_tex;
	}
};

struct LemonMenuLayer: Modify<LemonMenuLayer, MenuLayer> {
	void play_lemon() {
		auto system = FMODAudioEngine::get();
		auto audio = Mod::get()->getResourcesDir() / "lemon.ogg";

		system->playMusic(utils::string::pathToString(audio), true, 0.0f, 1);
	}

	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		play_lemon();

		return true;
	}
};

struct LemonSpriteFrameCache: Modify<LemonSpriteFrameCache, CCSpriteFrameCache> {
	using CCSpriteFrameCache::addSpriteFramesWithFile;

	void addSpriteFramesWithFile(const char* plist, const char* texture_filename) {
		CCSpriteFrameCache::addSpriteFramesWithFile(plist, texture_filename);

		if (!g_lemontex) {
			g_lemontex = CCTextureCache::sharedTextureCache()->addImage("lemon.png"_spr, false);
		}

		if (!g_lemontex) {
			return;
		}

		auto dict = CCDictionary::createWithContentsOfFile(plist);

		if (!dict) {
			return;
		}

		auto frames_dict = static_cast<CCDictionary*>(dict->objectForKey("frames"));

		if (!frames_dict) {
			return;
		}

		CCDictElement* element = nullptr;

		CCDICT_FOREACH(frames_dict, element) {
			const char* frame_name = element->getStrKey();
			auto frame = this->spriteFrameByName(frame_name);

			if (frame) {
				auto rect = frame->getRect();
				auto offset = frame->getOffset();
				auto orig_size = frame->getOriginalSize();

				auto new_frame = CCSpriteFrame::createWithTexture(
					g_lemontex,
					CCRect(0, 0, g_lemontex->getContentSize().width, g_lemontex->getContentSize().height)
				);

				new_frame->setOffset(offset);
				new_frame->setOriginalSize(orig_size);

				this->removeSpriteFrameByName(frame_name);
				this->addSpriteFrame(new_frame, frame_name);
			}
		}
	}

	void addSpriteFramesWithFile(const char* plist) {
		CCSpriteFrameCache::addSpriteFramesWithFile(plist);

		if (!g_lemontex) {
			g_lemontex = CCTextureCache::sharedTextureCache()->addImage("lemon.png"_spr, false);
		}

		if (!g_lemontex) {
			return;
		}

		auto dict = CCDictionary::createWithContentsOfFile(plist);
		if (!dict) {
			return;
		}

		auto frames_dict = static_cast<CCDictionary*>(dict->objectForKey("frames"));
		if (!frames_dict) {
			return;
		}

		CCDictElement* element = nullptr;
		CCDICT_FOREACH(frames_dict, element) {
			const char* frame_name = element->getStrKey();
			auto frame = this->spriteFrameByName(frame_name);

			if (frame) {
				auto rect = frame->getRect();
				auto offset = frame->getOffset();
				auto orig_size = frame->getOriginalSize();

				auto new_frame = CCSpriteFrame::createWithTexture(
					g_lemontex,
					CCRect(0, 0, g_lemontex->getContentSize().width, g_lemontex->getContentSize().height)
				);

				new_frame->setOffset(offset);
				new_frame->setOriginalSize(orig_size);

				this->removeSpriteFrameByName(frame_name);
				this->addSpriteFrame(new_frame, frame_name);
			}
		}
	}
};
