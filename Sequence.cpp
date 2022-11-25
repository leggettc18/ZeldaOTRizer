#include "Sequence.h"
#include "Types.h"

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