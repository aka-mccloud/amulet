#include "codec_properties.hpp"

CodecProperties::CodecProperties() {
    options[BITRATE] = "-b";
    options[SAMPLERATE] = "--resample";
    options[LOWPASS] = "--lowpass";
}

QStringList CodecProperties::toStringList() const {
    QStringList codecProps;

    QList<Options> keys = values.keys();
    QList<Options>::iterator it;

    for (it = keys.begin(); it != keys.end(); ++it) {
        codecProps += options[*it];
        codecProps += values[*it];
    }

    return codecProps;
}
