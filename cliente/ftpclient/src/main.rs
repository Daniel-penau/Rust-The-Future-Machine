#![allow(dead_code, mutable_transmutes, non_camel_case_types, non_snake_case,
         non_upper_case_globals, unused_assignments, unused_mut)]
#![register_tool(c2rust)]
#![feature(const_raw_ptr_to_usize_cast, register_tool)]
extern "C" {
    #[no_mangle]
    fn socket(__domain: libc::c_int, __type: libc::c_int,
              __protocol: libc::c_int) -> libc::c_int;
    #[no_mangle]
    fn connect(__fd: libc::c_int, __addr: *const sockaddr, __len: socklen_t)
     -> libc::c_int;
    #[no_mangle]
    fn send(__fd: libc::c_int, __buf: *const libc::c_void, __n: size_t,
            __flags: libc::c_int) -> ssize_t;
    #[no_mangle]
    fn recv(__fd: libc::c_int, __buf: *mut libc::c_void, __n: size_t,
            __flags: libc::c_int) -> ssize_t;
    #[no_mangle]
    fn inet_addr(__cp: *const libc::c_char) -> in_addr_t;
    #[no_mangle]
    fn memcpy(_: *mut libc::c_void, _: *const libc::c_void, _: libc::c_ulong)
     -> *mut libc::c_void;
    #[no_mangle]
    fn strcpy(_: *mut libc::c_char, _: *const libc::c_char)
     -> *mut libc::c_char;
    #[no_mangle]
    fn strcat(_: *mut libc::c_char, _: *const libc::c_char)
     -> *mut libc::c_char;
    #[no_mangle]
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    #[no_mangle]
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    #[no_mangle]
    fn scanf(_: *const libc::c_char, _: ...) -> libc::c_int;
    #[no_mangle]
    fn perror(__s: *const libc::c_char);
    #[no_mangle]
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    #[no_mangle]
    fn exit(_: libc::c_int) -> !;
    #[no_mangle]
    fn system(__command: *const libc::c_char) -> libc::c_int;
    #[no_mangle]
    fn stat(__file: *const libc::c_char, __buf: *mut stat) -> libc::c_int;
    #[no_mangle]
    fn sendfile(__out_fd: libc::c_int, __in_fd: libc::c_int,
                __offset: *mut off_t, __count: size_t) -> ssize_t;
    #[no_mangle]
    fn open(__file: *const libc::c_char, __oflag: libc::c_int, _: ...)
     -> libc::c_int;
    #[no_mangle]
    fn close(__fd: libc::c_int) -> libc::c_int;
    #[no_mangle]
    fn write(__fd: libc::c_int, __buf: *const libc::c_void, __n: size_t)
     -> ssize_t;
}
pub type __dev_t = libc::c_ulong;
pub type __uid_t = libc::c_uint;
pub type __gid_t = libc::c_uint;
pub type __ino_t = libc::c_ulong;
pub type __mode_t = libc::c_uint;
pub type __nlink_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __time_t = libc::c_long;
pub type __blksize_t = libc::c_long;
pub type __blkcnt_t = libc::c_long;
pub type __ssize_t = libc::c_long;
pub type __syscall_slong_t = libc::c_long;
pub type __socklen_t = libc::c_uint;
pub type off_t = __off_t;
pub type ssize_t = __ssize_t;
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct timespec {
    pub tv_sec: __time_t,
    pub tv_nsec: __syscall_slong_t,
}
pub type socklen_t = __socklen_t;
pub type __socket_type = libc::c_uint;
pub const SOCK_NONBLOCK: __socket_type = 2048;
pub const SOCK_CLOEXEC: __socket_type = 524288;
pub const SOCK_PACKET: __socket_type = 10;
pub const SOCK_DCCP: __socket_type = 6;
pub const SOCK_SEQPACKET: __socket_type = 5;
pub const SOCK_RDM: __socket_type = 4;
pub const SOCK_RAW: __socket_type = 3;
pub const SOCK_DGRAM: __socket_type = 2;
pub const SOCK_STREAM: __socket_type = 1;
pub type sa_family_t = libc::c_ushort;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sockaddr {
    pub sa_family: sa_family_t,
    pub sa_data: [libc::c_char; 14],
}
pub type uint16_t = libc::c_ushort;
pub type uint32_t = libc::c_uint;
pub type in_addr_t = uint32_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct in_addr {
    pub s_addr: in_addr_t,
}
pub type in_port_t = uint16_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sockaddr_in {
    pub sin_family: sa_family_t,
    pub sin_port: in_port_t,
    pub sin_addr: in_addr,
    pub sin_zero: [libc::c_uchar; 8],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct stat {
    pub st_dev: __dev_t,
    pub st_ino: __ino_t,
    pub st_nlink: __nlink_t,
    pub st_mode: __mode_t,
    pub st_uid: __uid_t,
    pub st_gid: __gid_t,
    pub __pad0: libc::c_int,
    pub st_rdev: __dev_t,
    pub st_size: __off_t,
    pub st_blksize: __blksize_t,
    pub st_blocks: __blkcnt_t,
    pub st_atim: timespec,
    pub st_mtim: timespec,
    pub st_ctim: timespec,
    pub __glibc_reserved: [__syscall_slong_t; 3],
}
// codigo de error de socket
#[no_mangle]
pub static mut server: sockaddr_in =
    sockaddr_in{sin_family: 0,
                sin_port: 0,
                sin_addr: in_addr{s_addr: 0,},
                sin_zero: [0; 8],};
#[no_mangle]
pub static mut socketServer: libc::c_int = 0;
#[no_mangle]
pub static mut buf: [libc::c_char; 100] = [0; 100];
#[no_mangle]
pub static mut f: *mut libc::c_char =
    0 as *const libc::c_char as *mut libc::c_char;
#[no_mangle]
pub static mut filename: [libc::c_char; 25] = [0; 25];
#[no_mangle]
pub static mut mensajeServer: [libc::c_char; 100] = [0; 100];
#[no_mangle]
pub static mut size: libc::c_int = 0;
#[no_mangle]
pub static mut status: libc::c_int = 0;
#[no_mangle]
pub static mut respuesta: libc::c_int = 0;
#[no_mangle]
pub static mut filehandle: libc::c_int = 0;
#[no_mangle]
pub static mut obj: stat =
    stat{st_dev: 0,
         st_ino: 0,
         st_nlink: 0,
         st_mode: 0,
         st_uid: 0,
         st_gid: 0,
         __pad0: 0,
         st_rdev: 0,
         st_size: 0,
         st_blksize: 0,
         st_blocks: 0,
         st_atim: timespec{tv_sec: 0, tv_nsec: 0,},
         st_mtim: timespec{tv_sec: 0, tv_nsec: 0,},
         st_ctim: timespec{tv_sec: 0, tv_nsec: 0,},
         __glibc_reserved: [0; 3],};
/*Funcion para hacer un check de errores de socket
* ejecuta una instruccion y muestra un mensaje de 
* error si falla */
#[no_mangle]
pub unsafe extern "C" fn check(mut exp: libc::c_int,
                               mut msg: *const libc::c_char) -> libc::c_int {
    if exp == -(1 as libc::c_int) { perror(msg); exit(1 as libc::c_int); }
    return exp;
}
/*Funcion que crea el socket del servidor*/
#[no_mangle]
pub unsafe extern "C" fn CrearSocket() {
    socketServer =
        socket(2 as libc::c_int, SOCK_STREAM as libc::c_int,
               0 as libc::c_int);
    check(socketServer,
          b"\nFallo la creacion del socket del cliente\n\x00" as *const u8 as
              *const libc::c_char);
}
#[no_mangle]
pub unsafe extern "C" fn Conectar() {
    check(connect(socketServer,
                  &mut server as *mut sockaddr_in as *mut sockaddr,
                  ::std::mem::size_of::<sockaddr_in>() as libc::c_ulong as
                      socklen_t),
          b"Fallo la conexion\x00" as *const u8 as *const libc::c_char);
}
unsafe fn main_0(mut argc: libc::c_int, mut argv: *mut *mut libc::c_char)
 -> libc::c_int {
    /* code */
    let mut inaddr: libc::c_ulong = 0;
    inaddr =
        inet_addr(*argv.offset(1 as libc::c_int as isize)) as libc::c_ulong;
    //printf("%s",argv[1]);
    CrearSocket(); //ftp standart port 20 o 21 para autenticarse
    server.sin_family = 2 as libc::c_int as sa_family_t;
    server.sin_port = 20 as libc::c_int as in_port_t;
    memcpy(&mut server.sin_addr as *mut in_addr as *mut libc::c_void,
           &mut inaddr as *mut libc::c_ulong as *const libc::c_void,
           ::std::mem::size_of::<libc::c_ulong>() as libc::c_ulong);
    Conectar();
    respuesta =
        recv(socketServer, mensajeServer.as_mut_ptr() as *mut libc::c_void,
             100 as libc::c_int as size_t, 0 as libc::c_int) as libc::c_int;
    mensajeServer[respuesta as usize] = '\u{0}' as i32 as libc::c_char;
    printf(b"\nRespuesta del servido> %s\x00" as *const u8 as
               *const libc::c_char, mensajeServer.as_mut_ptr());
    while strcmp(mensajeServer.as_mut_ptr(),
                 b"\nConectado\n\x00" as *const u8 as *const libc::c_char) !=
              0 {
        //system("clear");
        respuesta =
            recv(socketServer,
                 mensajeServer.as_mut_ptr() as *mut libc::c_void,
                 100 as libc::c_int as size_t, 0 as libc::c_int) as
                libc::c_int;
        mensajeServer[respuesta as usize] = '\u{0}' as i32 as libc::c_char
        //printf("\nRespuesta del servido> %s",mensajeServer);
    }
    let mut i: libc::c_int = 2 as libc::c_int;
    while i < argc {
        printf(b"\n argumento > %s\x00" as *const u8 as *const libc::c_char,
               *argv.offset(i as isize));
        if strcmp(*argv.offset(i as isize),
                  b"ls\x00" as *const u8 as *const libc::c_char) == 0 {
            strcpy(buf.as_mut_ptr(),
                   b"ls\x00" as *const u8 as *const libc::c_char);
            send(socketServer, buf.as_mut_ptr() as *const libc::c_void,
                 100 as libc::c_int as size_t, 0 as libc::c_int);
            recv(socketServer,
                 &mut size as *mut libc::c_int as *mut libc::c_void,
                 ::std::mem::size_of::<libc::c_int>() as libc::c_ulong,
                 0 as libc::c_int);
            //printf("\naca llegue\n");
            f = malloc(size as libc::c_ulong) as *mut libc::c_char;
            recv(socketServer, f as *mut libc::c_void, size as size_t,
                 0 as libc::c_int);
            filehandle =
                open(b"temp.txt\x00" as *const u8 as *const libc::c_char,
                     0o2 as libc::c_int | 0o100 as libc::c_int |
                         0o400 as libc::c_int | 0o200 as libc::c_int);
            write(filehandle, f as *const libc::c_void, size as size_t);
            close(filehandle);
            printf(b"\nEl ls del servidor es:\n\x00" as *const u8 as
                       *const libc::c_char);
            system(b"sudo cat temp.txt\x00" as *const u8 as
                       *const libc::c_char);
            system(b"unlink temp.txt\x00" as *const u8 as
                       *const libc::c_char);
        } else if strcmp(*argv.offset(i as isize),
                         b"cd\x00" as *const u8 as *const libc::c_char) == 0 {
            strcpy(buf.as_mut_ptr(),
                   b"cd\x00" as *const u8 as *const libc::c_char);
            printf(b"\n Escriba el directorio nuevo del servidor remoto: \x00"
                       as *const u8 as *const libc::c_char);
            scanf(b"%s\x00" as *const u8 as *const libc::c_char,
                  buf.as_mut_ptr().offset(3 as libc::c_int as isize));
            printf(b"\n%s\n\x00" as *const u8 as *const libc::c_char,
                   buf.as_mut_ptr().offset(3 as libc::c_int as isize));
            send(socketServer, buf.as_mut_ptr() as *const libc::c_void,
                 100 as libc::c_int as size_t, 0 as libc::c_int);
            printf(b"\ncontrol\n\x00" as *const u8 as *const libc::c_char);
            recv(socketServer,
                 &mut status as *mut libc::c_int as *mut libc::c_void,
                 ::std::mem::size_of::<libc::c_int>() as libc::c_ulong,
                 0 as libc::c_int);
            if status != 0 {
                printf(b"\nse cambio el directorio correctamente \n\x00" as
                           *const u8 as *const libc::c_char);
            } else {
                printf(b"\nFallo el cambio de directorio\n\x00" as *const u8
                           as *const libc::c_char);
            }
        } else if strcmp(*argv.offset(i as isize),
                         b"put\x00" as *const u8 as *const libc::c_char) == 0
         {
            printf(b"\nIngrese el nombre del archivo a subir: \x00" as
                       *const u8 as *const libc::c_char);
            scanf(b"%s\x00" as *const u8 as *const libc::c_char,
                  filename.as_mut_ptr());
            filehandle = open(filename.as_mut_ptr(), 0 as libc::c_int);
            check(filehandle,
                  b"\nError:el archivo no existe en el directorio\n\x00" as
                      *const u8 as *const libc::c_char);
            strcpy(buf.as_mut_ptr(),
                   b"put \x00" as *const u8 as *const libc::c_char);
            strcat(buf.as_mut_ptr(), filename.as_mut_ptr());
            send(socketServer, buf.as_mut_ptr() as *const libc::c_void,
                 100 as libc::c_int as size_t, 0 as libc::c_int);
            stat(filename.as_mut_ptr(), &mut obj);
            size = obj.st_size as libc::c_int;
            send(socketServer,
                 &mut size as *mut libc::c_int as *const libc::c_void,
                 ::std::mem::size_of::<libc::c_int>() as libc::c_ulong,
                 0 as libc::c_int);
            sendfile(socketServer, filehandle, 0 as *mut off_t,
                     size as size_t);
            recv(socketServer,
                 &mut status as *mut libc::c_int as *mut libc::c_void,
                 ::std::mem::size_of::<libc::c_int>() as libc::c_ulong,
                 0 as libc::c_int);
            if status != 0 {
                printf(b"\nSe agrago correctamente el archivo al servidor\x00"
                           as *const u8 as *const libc::c_char);
            } else {
                printf(b"\nFallo al agregar el archivo al servidor\x00" as
                           *const u8 as *const libc::c_char);
            }
        } else if strcmp(*argv.offset(i as isize),
                         b"get\x00" as *const u8 as *const libc::c_char) == 0
         {
            printf(b"\nIngrese el nombre del archivo a obtener: \x00" as
                       *const u8 as *const libc::c_char);
            scanf(b"%s\x00" as *const u8 as *const libc::c_char,
                  filename.as_mut_ptr());
            strcpy(buf.as_mut_ptr(),
                   b"get \x00" as *const u8 as *const libc::c_char);
            strcat(buf.as_mut_ptr(), filename.as_mut_ptr());
            send(socketServer, buf.as_mut_ptr() as *const libc::c_void,
                 100 as libc::c_int as size_t, 0 as libc::c_int);
            recv(socketServer,
                 &mut size as *mut libc::c_int as *mut libc::c_void,
                 ::std::mem::size_of::<libc::c_int>() as libc::c_ulong,
                 0 as libc::c_int);
            filehandle =
                open(filename.as_mut_ptr(),
                     0o100 as libc::c_int | 0o200 as libc::c_int |
                         0o1 as libc::c_int, 0o666 as libc::c_int);
            if filehandle == -(1 as libc::c_int) {
                printf(b"\nerror al crear el archivo a guardar\n\x00" as
                           *const u8 as *const libc::c_char);
            }
            f = malloc(size as libc::c_ulong) as *mut libc::c_char;
            recv(socketServer, f as *mut libc::c_void, size as size_t,
                 0 as libc::c_int);
            write(filehandle, f as *const libc::c_void, size as size_t);
            close(filehandle);
        }
        i += 1
    }
    return 0 as libc::c_int;
}
#[main]
pub fn main() {
    let mut args: Vec<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(::std::ffi::CString::new(arg).expect("Failed to convert argument into CString.").into_raw());
    };
    args.push(::std::ptr::null_mut());
    unsafe {
        ::std::process::exit(main_0((args.len() - 1) as libc::c_int,
                                    args.as_mut_ptr() as
                                        *mut *mut libc::c_char) as i32)
    }
}

