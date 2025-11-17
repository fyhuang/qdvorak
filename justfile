build:
    rm -rf zsa_firmware/keyboards/zsa/moonlander/keymaps/qdvorak
    cp -R moonlander/qdvorak zsa_firmware/keyboards/zsa/moonlander/keymaps/qdvorak
    cd zsa_firmware && qmk compile -kb moonlander -km qdvorak

setup:
    cd zsa_firmware && qmk setup zsa/qmk_firmware -b firmware25
