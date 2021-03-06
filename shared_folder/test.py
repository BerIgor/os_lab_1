#!/usr/bin/python

from __future__ import division
from struct import calcsize
import fcntl
import os

#
# Globals
#
DEVICE_PATH = '/dev/my_device0'


#
# Utilities for calculating the IOCTL command codes.
#
sizeof = {
    'byte': calcsize('c'),
    'signed byte': calcsize('b'),
    'unsigned byte': calcsize('B'),
    'short': calcsize('h'),
    'unsigned short': calcsize('H'),
    'int': calcsize('i'),
    'unsigned int': calcsize('I'),
    'long': calcsize('l'),
    'unsigned long': calcsize('L'),
    'long long': calcsize('q'),
    'unsigned long long': calcsize('Q')
}

_IOC_NRBITS = 8
_IOC_TYPEBITS = 8
_IOC_SIZEBITS = 14
_IOC_DIRBITS = 2

_IOC_NRMASK = ((1 << _IOC_NRBITS)-1)
_IOC_TYPEMASK = ((1 << _IOC_TYPEBITS)-1)
_IOC_SIZEMASK = ((1 << _IOC_SIZEBITS)-1)
_IOC_DIRMASK = ((1 << _IOC_DIRBITS)-1)

_IOC_NRSHIFT = 0
_IOC_TYPESHIFT = (_IOC_NRSHIFT+_IOC_NRBITS)
_IOC_SIZESHIFT = (_IOC_TYPESHIFT+_IOC_TYPEBITS)
_IOC_DIRSHIFT = (_IOC_SIZESHIFT+_IOC_SIZEBITS)

_IOC_NONE = 0
_IOC_WRITE = 1
_IOC_READ = 2

def _IOC(dir, _type, nr, size):
    if type(_type) == str:
        _type = ord(_type)
        
    cmd_number = (((dir)  << _IOC_DIRSHIFT) | \
        ((_type) << _IOC_TYPESHIFT) | \
        ((nr)   << _IOC_NRSHIFT) | \
        ((size) << _IOC_SIZESHIFT))

    return cmd_number

def _IO(_type, nr):
    return _IOC(_IOC_NONE, _type, nr, 0)

def _IOR(_type, nr, size):
    return _IOC(_IOC_READ, _type, nr, sizeof[size])

def _IOW(_type, nr, size):
    return _IOC(_IOC_WRITE, _type, nr, sizeof[size])


def main():
    """Test the device driver"""
    
    #
    # Calculate the ioctl cmd number
    #
    MY_MAGIC = 'r'
    MY_OP1 = _IOW(MY_MAGIC, 0, 'int')
    
    #
    # Open the 'my_moulde' device driver
    #
    f = os.open(DEVICE_PATH, os.O_RDWR)
    
    #
    # Test writing and reading
    #
    os.write(f, 'hello world')
    print 'String read:\n%s' % os.read(f, 30)

    #
    # Test the IOCTL command
    #
    fcntl.ioctl(f, MY_OP1)    

    #
    # Finaly close the file
    #
    os.close(f)

    
if __name__ == '__main__':
    main()
    
