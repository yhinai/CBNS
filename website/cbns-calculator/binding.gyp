{
  "targets": [
    {
      "target_name": "addon",
      "cflags!": [ "-std=clang++ -fno-exceptions" ],
      "cflags_cc!": [ "-std=clang++ -fno-exceptions" ],
        'xcode_settings': {
    'GCC_ENABLE_CPP_EXCEPTIONS': 'NO',
    'CLANG_CXX_LANGUAGE_STANDARD': 'gnu++11',
    'CLANG_CXX_LIBRARY': 'libc++',
    'MACOSX_DEPLOYMENT_TARGET': '10.7',
  },
  'msvs_settings': {
    'VCCLCompilerTool': { 'ExceptionHandling': 1 },
  },
      "sources": [ "src/calculator.cc"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}