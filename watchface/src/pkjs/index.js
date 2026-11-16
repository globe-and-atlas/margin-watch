var Clay = require('@rebble/clay');
var defaults = {Palette: 0, Background: 0xFFFFFF, Foreground: 0, Accent: 0xAA0000, TimeFormat: 0, DateFormat: 1};

function integer(value, fallback, maximum) {
  if (value === undefined || value === null || value === '' || typeof value === 'boolean') return fallback;
  var number = Number(value);
  return isFinite(number) && Math.floor(number) === number && number >= 0 && number <= maximum ? number : fallback;
}
function normalize(raw) {
  raw = raw || {};
  return {
    Palette: integer(raw.Palette, defaults.Palette, 6),
    Background: integer(raw.Background, defaults.Background, 0xFFFFFF),
    Foreground: integer(raw.Foreground, defaults.Foreground, 0xFFFFFF),
    Accent: integer(raw.Accent, defaults.Accent, 0xFFFFFF),
    TimeFormat: integer(raw.TimeFormat, defaults.TimeFormat, 2),
    DateFormat: integer(raw.DateFormat, defaults.DateFormat, 4)
  };
}
var clay = new Clay([
  {type: 'heading', defaultValue: 'Margin'},
  {type: 'text', defaultValue: 'Oversized time with date and battery in the margin. Numeric dates stack vertically in the selected order.'},
  {type: 'select', messageKey: 'TimeFormat', label: 'Time format', defaultValue: '0', options: [
    {label: 'Watch default', value: '0'}, {label: '12-hour', value: '1'}, {label: '24-hour', value: '2'}
  ]},
  {type: 'select', messageKey: 'DateFormat', label: 'Date', defaultValue: '1', options: [
    {label: 'Off', value: '0'}, {label: 'THU NOV 05', value: '1'},
    {label: 'YYYY-MM-DD', value: '2'}, {label: 'MM/DD/YYYY', value: '3'}, {label: 'DD/MM/YYYY', value: '4'}
  ]},
  {type: 'heading', defaultValue: 'Colors'},
  {type: 'select', messageKey: 'Palette', label: 'Palette', defaultValue: '0', options: [
    {label: 'Paper — black & red', value: '0'}, {label: 'Cream', value: '1'},
    {label: 'Night', value: '2'}, {label: 'Ice', value: '3'}, {label: 'Mint', value: '4'},
    {label: 'Plum', value: '5'}, {label: 'Custom colors', value: '6'}
  ]},
  {type: 'text', defaultValue: 'Select Custom colors to use the choices below. The accent colors the divider and minute-progress line. Choose contrasting text and background colors.'},
  {type: 'color', messageKey: 'Background', label: 'Background', defaultValue: 'FFFFFF', sunlight: false, allowGray: true},
  {type: 'color', messageKey: 'Foreground', label: 'Digits & labels', defaultValue: '000000', sunlight: false, allowGray: true},
  {type: 'color', messageKey: 'Accent', label: 'Accent', defaultValue: 'AA0000', sunlight: false, allowGray: true},
  {type: 'submit', defaultValue: 'Save to watch'}
], null, {autoHandleEvents: false});

function sendSaved() {
  var raw = localStorage.getItem('clay-settings');
  if (!raw) return;
  try { Pebble.sendAppMessage(normalize(JSON.parse(raw))); } catch (error) { console.log('Margin settings could not be loaded'); }
}
Pebble.addEventListener('ready', sendSaved);
Pebble.addEventListener('showConfiguration', function() { Pebble.openURL(clay.generateUrl()); });
Pebble.addEventListener('webviewclosed', function(event) {
  if (!event || !event.response || event.response === 'CANCELLED') return;
  try {
    clay.getSettings(event.response, false);
    sendSaved();
  } catch (error) { console.log('Margin settings were not saved'); }
});

module.exports = {normalize: normalize, defaults: defaults};
