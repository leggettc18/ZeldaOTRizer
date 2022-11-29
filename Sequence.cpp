#include "Sequence.h"
#include "Types.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

ZeldaOTRizer::Sequence::Sequence(std::shared_ptr<Ship::Archive> otrFile, const char* outPath)
    : OTRizer::Resource(otrFile, outPath, static_cast<int>(ResourceTypes::AudioSequence),
                        static_cast<int>(GameVersions::Rachael), resourceVersions[ResourceTypes::AudioSequence]) {
}

void ZeldaOTRizer::Sequence::WriteResourceData() {
    writer->Write((uint32_t)Size);
    writer->Write(RawBinary.data(), Size);
    writer->Write(SequenceNum);
    writer->Write(Medium);
    writer->Write(CachePolicy);
    writer->Write(NumFonts);
    for (uint32_t i = 0; i < NumFonts; i++) {
        writer->Write(FontIndices[i]);
    }
}

ZeldaOTRizer::Sequence
ZeldaOTRizer::Sequence::FromSeqFile(std::shared_ptr<Ship::Archive> otrFile, const std::filesystem::path& fileName) {
    // Use the existing path and the sequence's corresponding .meta file to construct the resource
    // and OTR Database Name.
    std::string metaName;
    uint8_t fontIdx;
    std::vector<std::string> splitPath = StringUtils::Split(fileName.generic_string(), ".");
    if (splitPath.size() >= 2) {
        splitPath.pop_back();
    }
    std::string afterPath =
        std::accumulate(splitPath.begin(), splitPath.end(), std::string(),
                        [](std::string lhs, const std::string& rhs) { return lhs.empty() ? rhs : lhs + '.' + rhs; });
    // Parse the .meta file.
    std::ifstream metaFile(afterPath + ".meta");
    // Replace the file name with the name from the .meta file.
    if (std::getline(metaFile, metaName)) {
        StringUtils::ReplaceOriginal(metaName, "/", "|");
        afterPath = "custom/music/" + metaName;
    }
    // Get the font(s) from the .meta file eventually this should support multiple,
    // but for now only one.
    std::string metaFontIdx;
    if (std::getline(metaFile, metaFontIdx)) {
        fontIdx = stoi(metaFontIdx, nullptr, 16);
    }
    // Get the sequence type (for now it will be either bgm or fanfare).
    std::string type;
    if (!std::getline(metaFile, type)) {
        type = "bgm";
    }
    // append the type to the database name for later extraction by the game.
    std::locale loc;
    for (int i = 0; i < type.length(); i++) {
        type[i] = std::tolower(type[i], loc);
    }
    afterPath += ("_" + type);
    // Create the Sequence Resource.
    ZeldaOTRizer::Sequence sequence(otrFile, afterPath.c_str());
    std::vector<char> binaryData = FileUtils::ReadAllBytes(fileName);
    sequence.Size = binaryData.size();
    sequence.RawBinary = std::vector<char>(binaryData.size());
    memcpy(sequence.RawBinary.data(), binaryData.data(), binaryData.size());
    sequence.CachePolicy = (type == "bgm" ? 2 : 1);
    sequence.Medium = 2;
    sequence.SequenceNum = 0;
    sequence.NumFonts = 1;
    sequence.FontIndices = { fontIdx };
    return sequence;
}