# qtposition_gpsd
Qt Position plugin for gpsd

Tested with Qt 5.4.1

## Usage

### Installation

For making the plugin accessible from your application, there are a number of standard locations for it:
* the global plugin directory (e.g. `$QTDIR/plugins`)
* a local subdirectory of your application folder (`position` for position plugins)

More information about plugins are to be found in the Qt documentation. For debugging plugin resolution it can be useful to set the environment variable `QT_DEBUG_PLUGINS` to 1. The plugin itself will print debug output if compiled with `CONFIG += debug`.

The `satelliteinfo` example from the qtlocation module can be used for quick testing. 

### Environment variables

By default, the plugin tries to connect to a locally running gpsd at the standard port 2947. This behaviour can be adjusted by setting the environment variables `GPSD_HOST` and `GPSD_PORT`.
