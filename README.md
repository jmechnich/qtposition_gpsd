# qtposition_gpsd
Qt Position plugin for gpsd

Tested with Qt 5.4.1

## Usage

### Installation

For making the plugin accessible from your application, there are a number of standard locations for it:
* the global plugin directory (e.g. <tt>$QTDIR/plugins</tt>)
* a local subdirectory of your application folder (<tt>position</tt> for position plugins)

More information about plugins are to be found in the Qt documentation. For debugging purposes it can be useful to set the environment variable<tt>QT_DEBUG_PLUGINS</tt>.

### Environment variables

By default, the plugin tries to connect to a locally running gpsd at the standard port 2947. This behaviour can be adjusted by setting the environment variables <tt>GPSD_HOST</tt> and <tt>GPSD_PORT</tt>.
