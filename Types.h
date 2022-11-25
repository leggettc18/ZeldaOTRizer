#include <unordered_map>

namespace ZeldaOTRizer {
enum class GameVersions { Deckard, Roy, Rachael, Zhora, Flynn };
enum class ResourceTypes { AudioSequence = 0x4F534551 };
};

static std::unordered_map<ZeldaOTRizer::ResourceTypes, uint32_t> resourceVersions = {
    { ZeldaOTRizer::ResourceTypes::AudioSequence, 0 },
};