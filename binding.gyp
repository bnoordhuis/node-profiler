{
  'targets': [
    {
      'target_name': 'profiler',
      'sources': ['profiler.cc']
    },

    {
      'target_name': 'nprof',
      'conditions': [
        # requires a posix shell
        ['OS != "win"', {
          'actions': [{
            'action_name': 'nprof',
            'inputs': [
              'tools/nprof-stub.js',
              'tools/v8/splaytree.js',
              'tools/v8/codemap.js',
              'tools/v8/csvparser.js',
              'tools/v8/consarray.js',
              'tools/v8/profile.js',
              'tools/v8/profile_view.js',
              'tools/v8/logreader.js',
              'tools/v8/tickprocessor.js',
              'tools/v8/tickprocessor-driver.js',
            ],
            'outputs': ['<(PRODUCT_DIR)/nprof'],
            'action': ['tools/build-nprof', '<@(_outputs)'],
          }],
        }],
      ],
    },
  ]
}
