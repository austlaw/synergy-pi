# Snippet from https://github.com/girst/hardpass-sendHID/blob/master/README.md . In which, the following notice was left:

# this is a stripped down version of https://github.com/ckuethe/usbarmory/wiki/USB-Gadgets - I don't claim any rights


# Linux only
if [ "$(lsusb)" != "Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub" ]
then
  echo "Only works on linux"
  exit 1
fi


modprobe libcomposite
cd /sys/kernel/config/usb_gadget/
mkdir -p g1
cd g1
echo 0x1d6b > idVendor # Linux Foundation
echo 0x0104 > idProduct # Multifunction Composite Gadget
echo 0x0100 > bcdDevice # v1.0.0
echo 0x0200 > bcdUSB # USB2
mkdir -p strings/0x409
echo "kvmpi038fd9j329" > strings/0x409/serialnumber
echo "kvmpi" > strings/0x409/manufacturer
echo "KVM" > strings/0x409/product

A_N="keyboard"
mkdir -p functions/hid.$A_N
echo 1 > functions/hid.$A_N/protocol
echo 1 > functions/hid.$A_N/subclass
echo 8 > functions/hid.$A_N/report_length
echo -ne \\x05\\x01\\x09\\x06\\xa1\\x01\\x05\\x07\\x19\\xe0\\x29\\xe7\\x15\\x00\\x25\\x01\\x75\\x01\\x95\\x08\\x81\\x02\\x95\\x01\\x75\\x08\\x81\\x03\\x95\\x05\\x75\\x01\\x05\\x08\\x19\\x01\\x29\\x05\\x91\\x02\\x95\\x01\\x75\\x03\\x91\\x03\\x95\\x06\\x75\\x08\\x15\\x00\\x25\\x65\\x05\\x07\\x19\\x00\\x29\\x65\\x81\\x00\\xc0 > functions/hid.$A_N/report_desc

B_N="mouse"
mkdir -p functions/hid.$B_N
echo 2 > functions/hid.$B_N/protocol
echo 1 > functions/hid.$B_N/subclass
echo 3 > functions/hid.$B_N/report_length
echo -ne \\x05\\x01\\x09\\x02\\xa1\\x01\\x09\\x01\\xa1\\x00\\x05\\x09\\x19\\x01\\x29\\x03\\x15\\x00\\x25\\x01\\x95\\x03\\x75\\x01\\x81\\x02\\x95\\x01\\x75\\x05\\x81\\x03\\x05\\x01\\x09\\x30\\x09\\x31\\x15\\x81\\x25\\x7F\\x75\\x08\\x95\\x02\\x81\\x02\\xc0\\xc0 > functions/hid.$B_N/report_desc
# 16 bit echo -ne \\x05\\x01\\x09\\x02\\xA1\\x01\\x09\\x01\\xA1\\x00\\x05\\x09\\x19\\x01\\x29\\x03\\x15\\x00\\x25\\x01\\x95\\x03\\x75\\x01\\x81\\x02\\x95\\x01\\x75\\x05\\x81\\x03\\x05\\x01\\x09\\x30\\x09\\x31\\x16\\x01\\x80\\x26\\xFF\\x7F\\x75\\x10\\x95\\x02\\x81\\x06\\xC0\\xC0 > functions/hid.$B_N/report_desc

C_N="mouse_abs"
mkdir -p functions/hid.$C_N
echo 2 > functions/hid.$C_N/protocol
echo 1 > functions/hid.$C_N/subclass
echo 3 > functions/hid.$C_N/report_length
echo -ne \\x05\\x01\\x09\\x02\\xa1\\x01\\x09\\x01\\xa1\\x00\\x05\\x09\\x19\\x01\\x29\\x03\\x15\\x00\\x25\\x01\\x95\\x03\\x75\\x01\\x81\\x02\\x95\\x01\\x75\\x05\\x81\\x03\\x05\\x01\\x09\\x30\\x09\\x31\\x15\\x00\\x26\\xFF\\x7F\\x75\\x10\\x95\\x02\\x81\\x02\\xc0\\xc0 > functions/hid.$B_N/report_desc

D=1
mkdir -p configs/c.$D/strings/0x409
echo "Config $D: ECM network" > configs/c.$D/strings/0x409/configuration
echo 250 > configs/c.$D/MaxPower
ln -s functions/hid.$A_N configs/c.$D/
ln -s functions/hid.$B_N configs/c.$D/
ln -s functions/hid.$C_N configs/c.$D/
ls /sys/class/udc > UDC


chmod -R 777 /dev/hidg0
chmod -R 777 /dev/hidg1
