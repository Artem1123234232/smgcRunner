set(CMAKE_CXX_COMPILER "/run/current-system/sw/bin/g++")
set(CMAKE_CXX_COMPILER_ARG1 "")
set(CMAKE_CXX_COMPILER_ID "GNU")
set(CMAKE_CXX_COMPILER_VERSION "15.2.0")
set(CMAKE_CXX_COMPILER_VERSION_INTERNAL "")
set(CMAKE_CXX_COMPILER_WRAPPER "")
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "17")
set(CMAKE_CXX_EXTENSIONS_COMPUTED_DEFAULT "ON")
set(CMAKE_CXX_STANDARD_LATEST "26")
set(CMAKE_CXX_COMPILE_FEATURES "cxx_std_98;cxx_template_template_parameters;cxx_std_11;cxx_alias_templates;cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_decltype;cxx_decltype_incomplete_return_types;cxx_default_function_template_args;cxx_defaulted_functions;cxx_defaulted_move_initializers;cxx_delegating_constructors;cxx_deleted_functions;cxx_enum_forward_declarations;cxx_explicit_conversions;cxx_extended_friend_declarations;cxx_extern_templates;cxx_final;cxx_func_identifier;cxx_generalized_initializers;cxx_inheriting_constructors;cxx_inline_namespaces;cxx_lambdas;cxx_local_type_template_args;cxx_long_long_type;cxx_noexcept;cxx_nonstatic_member_init;cxx_nullptr;cxx_override;cxx_range_for;cxx_raw_string_literals;cxx_reference_qualified_functions;cxx_right_angle_brackets;cxx_rvalue_references;cxx_sizeof_member;cxx_static_assert;cxx_strong_enums;cxx_thread_local;cxx_trailing_return_types;cxx_unicode_literals;cxx_uniform_initialization;cxx_unrestricted_unions;cxx_user_literals;cxx_variadic_macros;cxx_variadic_templates;cxx_std_14;cxx_aggregate_default_initializers;cxx_attribute_deprecated;cxx_binary_literals;cxx_contextual_conversions;cxx_decltype_auto;cxx_digit_separators;cxx_generic_lambdas;cxx_lambda_init_captures;cxx_relaxed_constexpr;cxx_return_type_deduction;cxx_variable_templates;cxx_std_17;cxx_std_20;cxx_std_23;cxx_std_26")
set(CMAKE_CXX98_COMPILE_FEATURES "cxx_std_98;cxx_template_template_parameters")
set(CMAKE_CXX11_COMPILE_FEATURES "cxx_std_11;cxx_alias_templates;cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_decltype;cxx_decltype_incomplete_return_types;cxx_default_function_template_args;cxx_defaulted_functions;cxx_defaulted_move_initializers;cxx_delegating_constructors;cxx_deleted_functions;cxx_enum_forward_declarations;cxx_explicit_conversions;cxx_extended_friend_declarations;cxx_extern_templates;cxx_final;cxx_func_identifier;cxx_generalized_initializers;cxx_inheriting_constructors;cxx_inline_namespaces;cxx_lambdas;cxx_local_type_template_args;cxx_long_long_type;cxx_noexcept;cxx_nonstatic_member_init;cxx_nullptr;cxx_override;cxx_range_for;cxx_raw_string_literals;cxx_reference_qualified_functions;cxx_right_angle_brackets;cxx_rvalue_references;cxx_sizeof_member;cxx_static_assert;cxx_strong_enums;cxx_thread_local;cxx_trailing_return_types;cxx_unicode_literals;cxx_uniform_initialization;cxx_unrestricted_unions;cxx_user_literals;cxx_variadic_macros;cxx_variadic_templates")
set(CMAKE_CXX14_COMPILE_FEATURES "cxx_std_14;cxx_aggregate_default_initializers;cxx_attribute_deprecated;cxx_binary_literals;cxx_contextual_conversions;cxx_decltype_auto;cxx_digit_separators;cxx_generic_lambdas;cxx_lambda_init_captures;cxx_relaxed_constexpr;cxx_return_type_deduction;cxx_variable_templates")
set(CMAKE_CXX17_COMPILE_FEATURES "cxx_std_17")
set(CMAKE_CXX20_COMPILE_FEATURES "cxx_std_20")
set(CMAKE_CXX23_COMPILE_FEATURES "cxx_std_23")
set(CMAKE_CXX26_COMPILE_FEATURES "cxx_std_26")

set(CMAKE_CXX_PLATFORM_ID "Linux")
set(CMAKE_CXX_SIMULATE_ID "")
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT "GNU")
set(CMAKE_CXX_COMPILER_APPLE_SYSROOT "")
set(CMAKE_CXX_SIMULATE_VERSION "")
set(CMAKE_CXX_COMPILER_ARCHITECTURE_ID "x86_64")



set(CMAKE_AR "/run/current-system/sw/bin/ar")
set(CMAKE_CXX_COMPILER_AR "/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/bin/gcc-ar")
set(CMAKE_RANLIB "/run/current-system/sw/bin/ranlib")
set(CMAKE_CXX_COMPILER_RANLIB "/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/bin/gcc-ranlib")
set(CMAKE_LINKER "/run/current-system/sw/bin/ld")
set(CMAKE_LINKER_LINK "")
set(CMAKE_LINKER_LLD "")
set(CMAKE_CXX_COMPILER_LINKER "/nix/store/la0zcwbbm1jazcjqf80m49xfyj14k4b3-binutils-wrapper-2.46/bin/ld")
set(CMAKE_CXX_COMPILER_LINKER_ID "GNU")
set(CMAKE_CXX_COMPILER_LINKER_VERSION 2.46)
set(CMAKE_CXX_COMPILER_LINKER_FRONTEND_VARIANT GNU)
set(CMAKE_MT "")
set(CMAKE_TAPI "CMAKE_TAPI-NOTFOUND")
set(CMAKE_COMPILER_IS_GNUCXX 1)
set(CMAKE_CXX_COMPILER_LOADED 1)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_CXX_ABI_COMPILED TRUE)

set(CMAKE_CXX_COMPILER_ENV_VAR "CXX")

set(CMAKE_CXX_COMPILER_ID_RUN 1)
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS C;M;c++;cc;cpp;cxx;m;mm;mpp;CPP;ixx;cppm;ccm;cxxm;c++m)
set(CMAKE_CXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O;obj;OBJ;def;DEF;rc;RC)

foreach (lang IN ITEMS C OBJC OBJCXX)
  if (CMAKE_${lang}_COMPILER_ID_RUN)
    foreach(extension IN LISTS CMAKE_${lang}_SOURCE_FILE_EXTENSIONS)
      list(REMOVE_ITEM CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${extension})
    endforeach()
  endif()
endforeach()

set(CMAKE_CXX_LINKER_PREFERENCE 30)
set(CMAKE_CXX_LINKER_PREFERENCE_PROPAGATES 1)
set(CMAKE_CXX_LINKER_DEPFILE_SUPPORTED TRUE)
set(CMAKE_LINKER_PUSHPOP_STATE_SUPPORTED TRUE)
set(CMAKE_CXX_LINKER_PUSHPOP_STATE_SUPPORTED TRUE)

# Save compiler ABI information.
set(CMAKE_CXX_SIZEOF_DATA_PTR "8")
set(CMAKE_CXX_COMPILER_ABI "ELF")
set(CMAKE_CXX_BYTE_ORDER "LITTLE_ENDIAN")
set(CMAKE_CXX_LIBRARY_ARCHITECTURE "")

if(CMAKE_CXX_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_CXX_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_CXX_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_CXX_COMPILER_ABI}")
endif()

if(CMAKE_CXX_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_CXX_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_CXX_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES "/nix/store/ab5kmdi25sdwby91zz7n80kmx4kmjh67-glfw-3.4-dev/include;/nix/store/2vvzfir1v357j5qfqfqv5zclklln5lp2-libglvnd-1.7.0-dev/include;/nix/store/f4vkd1l8s292z8z40vpgw9hyz63q8dkm-glu-9.0.3-dev/include;/nix/store/gi5xksz4gd77q6rhvsaids0jbkxdpk0d-libx11-1.8.13-dev/include;/nix/store/2xc76y8jf3wnazrvmqc7ivc811jpx6q3-xorgproto-2025.1/include;/nix/store/f1hgjrhpi5ixh7y1m1w8iv0daysg01xs-libxrandr-1.5.5-dev/include;/nix/store/f3p9hzcrcz6ifsv8ipw1nmxsns3m1ij9-libxrender-0.9.12-dev/include;/nix/store/5ry9xdy9rplksmvapz784p6yibls8al1-libxcursor-1.2.3-dev/include;/nix/store/fki3lrr5p5741sgr4b7yzrja236rh4km-libxi-1.8.3-dev/include;/nix/store/rr5a618vbixmy0x7d8agh44rwa186svg-libxext-1.3.7-dev/include;/nix/store/m0vfslgsirkxkha7s1i37ydqcf07vsjm-libxau-1.0.12-dev/include;/nix/store/251ijhk6qqbhivknb104xl7sapcg2a2c-libxfixes-6.0.2-dev/include;/nix/store/ban38kbr1ixg00wg5f0jwz6z6vcmdg8x-libxinerama-1.1.6-dev/include;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/include/c++/15.2.0;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/include/c++/15.2.0/x86_64-unknown-linux-gnu;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/include/c++/15.2.0/backward;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/lib/gcc/x86_64-unknown-linux-gnu/15.2.0/include;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/include;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/lib/gcc/x86_64-unknown-linux-gnu/15.2.0/include-fixed;/nix/store/rlrznkmvs6jyp5kgq5jv2wqam83jv1r7-glibc-2.42-84-dev/include")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "stdc++;m;gcc_s;gcc;c;gcc_s;gcc")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "/nix/store/ji9sy2cadldwn33hm0aiiq8jld29rbq5-libglvnd-1.7.0/lib;/nix/store/fs5ac9zhj5wcm9vhzan9l7a4plgnczl0-glfw-3.4/lib;/nix/store/450mrbh6bp5m0f9g4llc7h8z5pcr0wkz-glu-9.0.3/lib;/nix/store/2g9xwk5kis01003gynr7xfca667dpgv8-libx11-1.8.13/lib;/nix/store/ibda7wki9fzqzwijp0d3857igk98is81-libxrender-0.9.12/lib;/nix/store/f7cisjakdl16hgfzxz7crhc95r7spmxy-libxrandr-1.5.5/lib;/nix/store/b35ckvyhs8r35s6wvgc6zzcq821a4bdi-libxcursor-1.2.3/lib;/nix/store/1w9qgjv9pcmgqmlzrdc0qml4nfsp5p2f-libxau-1.0.12/lib;/nix/store/c9asg9zdzspijnqay6jz1ddsxpaa2dvw-libxext-1.3.7/lib;/nix/store/16qnzpcnv6fy8h463744vrn0g4cpx86r-libxfixes-6.0.2/lib;/nix/store/gc2vc89xbjb59lyci28rwsz0hz5j1drz-libxi-1.8.3/lib;/nix/store/abb82846ndc6rjjcc0ybvqn5wshh7dhn-libxinerama-1.1.6/lib;/nix/store/rkiwrqh8g6gs5rws4bf1s3mrdcs15gm9-glibc-2.42-84/lib;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/lib/gcc/x86_64-unknown-linux-gnu/15.2.0;/nix/store/3b7njvjfc2w5lhj1jklrsw4lq7nwypri-gcc-15.2.0-lib/lib;/nix/store/6hjng4hd5c688hjgdcyb1rzfjz220srh-gcc-15.2.0/lib")
set(CMAKE_CXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
set(CMAKE_CXX_COMPILER_CLANG_RESOURCE_DIR "")

set(CMAKE_CXX_COMPILER_IMPORT_STD "")
### Imported target for C++23 standard library
set(CMAKE_CXX23_COMPILER_IMPORT_STD_NOT_FOUND_MESSAGE "Experimental `import std` support not enabled when detecting toolchain; it must be set before `CXX` is enabled (usually a `project()` call)")


### Imported target for C++26 standard library
set(CMAKE_CXX26_COMPILER_IMPORT_STD_NOT_FOUND_MESSAGE "Experimental `import std` support not enabled when detecting toolchain; it must be set before `CXX` is enabled (usually a `project()` call)")



