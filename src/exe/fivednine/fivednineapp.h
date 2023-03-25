#pragma once

#include "gameinfo.h"
#include "gamecard.h"
#include "eventpump.h"
#include "carouselselector.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <fivednine/render/texturestorage.h>
#include <fivednine/render/shaderstorage.h>

namespace fivednine 
{
    namespace render 
    {
        class Window;
    }
}

class AppConfig;
class fivednineApp
{
    public:
        bool Initialize(const AppConfig& configuration);
        void SetWindow(fivednine::render::Window* pWindow);

        void Tick(float dtSeconds);
        void Draw();

        // TODO: factor these out into a designated, C-friendly selector API
        // Attempting to make the selector itself stateless for future
        // hot-loading and language binding ambitions.
        uint32_t Selector_GetNumCards();
        void     Selector_SelectIndex(uint32_t index);
        uint32_t Selector_GetSelectedIndex();
        void     Selector_ConfirmCurrentSelection();

        void Selector_GetDisplayDimensions(uint32_t* pWidthOut, uint32_t* pHeightOut);
        bool Selector_GetCardGameInfo(uint32_t index, GameInfo* pGameInfoOut);
        bool Selector_SetCardAppearanceParam1f(uint32_t index, const char* pParameterName, float* pValue);
        bool Selector_SetCardPosition(uint32_t index, float x, float y, float z);
        bool Selector_SetCardDimensions(uint32_t index, float width, float height);
        bool Selector_SetCardTexture(uint32_t index, const char* pTextureName);

    private:
        bool LoadTextures(const AppConfig& configuration);
        bool LoadShaders(const AppConfig& configuration);
        bool LoadGamesInfo(const AppConfig& configuration);

    private:
        bool                       m_isInitialized = false;
        fivednine::render::Window* m_pWindow = nullptr;
        fivednine::render::TextureStorage m_textureStorage;
        fivednine::render::ShaderStorage  m_shaderStorage;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix; // TODO: Replace with camera

        // TODO: factor app state into common structure
        // TODO: static array container
        static constexpr uint8_t kMaxGameInfoEntries = 255; 
        GameInfo m_gameInfoArray[kMaxGameInfoEntries];
        uint8_t m_numGameInfos = 0;

        uint8_t m_currentSelectedCardIndex = 0;
        std::vector<GameCardPtr> m_gameCards;

        EventPump                         m_selectorEventPump;
        std::unique_ptr<CarouselSelector> m_spSelector;
};