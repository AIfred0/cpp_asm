#include <stdio.h>
#include <libusb-1.0/libusb.h>

void print_device_info(libusb_device *dev)
{
    // дескриптор устройства
    struct libusb_device_descriptor desc;
    // ф-ия, которая заполняет desc инфой об устройстве
    libusb_get_device_descriptor(dev, &desc);

    printf("Device Descriptor:\n");
    printf("  bLength             %u\n", desc.bLength);
    printf("  bDescriptorType     %u\n", desc.bDescriptorType);
    printf("  bcdUSB              %x\n", desc.bcdUSB);
    printf("  bDeviceClass        %u\n", desc.bDeviceClass);
    printf("  bDeviceSubClass     %u\n", desc.bDeviceSubClass);
    printf("  bDeviceProtocol     %u\n", desc.bDeviceProtocol);
    printf("  bMaxPacketSize0     %u\n", desc.bMaxPacketSize0);
    printf("  idVendor            %x\n", desc.idVendor);
    printf("  idProduct           %x\n", desc.idProduct);
    printf("  bcdDevice           %x\n", desc.bcdDevice);
    printf("  iManufacturer       %u\n", desc.iManufacturer);
    printf("  iProduct            %u\n", desc.iProduct);
    printf("  iSerialNumber       %u\n", desc.iSerialNumber);
    printf("  bNumConfigurations  %u\n", desc.bNumConfigurations);
}

int main()
{
    // указатель на массив указателей на usb
    libusb_device **devs;
    libusb_context *ctx = NULL;
    int r;
    ssize_t cnt;

    // если нет usb
    r = libusb_init(&ctx);
    if (r < 0)
    {
        printf("Initialization error %d\n", r);
        return 1;
    }

    // все usb
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0)
    {
        printf("Getting device list error %zd\n", cnt);
        return 1;
    }

    printf("Number of USB devices found: %zd\n", cnt);

    ssize_t i;
    for (i = 0; i < cnt; i++)
    {
        printf("\nDevice %zd:\n", i);
        print_device_info(devs[i]);
    }

    // освободить память
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}
