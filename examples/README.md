# Examples

## Setup

```bash
chmod +x install.sh
./install.sh
```

SDK library will be installed to `/lib/ps4-payload-sdk/libPS4`.

## Creating a Payload

Use `ps4-hello-world` as a template:

```bash
cp -r ps4-hello-world my-payload
cd my-payload
# edit source/main.c
make
```

This produces `my-payload.bin` in the current directory.

## Clean Build

```bash
make clean
```
