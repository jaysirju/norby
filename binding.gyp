{
  "targets": [
    {
      "target_name": "norby",
      "sources": [
        "src/Ruby.cpp",
        "src/RubyObject.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!(ruby -e 'puts RbConfig::CONFIG[\"rubyhdrdir\"]')",
        "<!(ruby -e 'puts RbConfig::CONFIG[\"rubyhdrdir\"] + \"/\" + RbConfig::CONFIG[\"arch\"]')"
      ],
      "library_dirs": [
        "<!(ruby -e 'puts RbConfig::CONFIG[\"libdir\"]')"
      ],
      "libraries": [
        "<!(ruby -e 'puts RbConfig::CONFIG[\"LIBRUBYARG\"]')",
        "-ldl"
      ]
    }
  ]
}
