# VanitySearch

VanitySearch is a groestlcoin address prefix finder. If you want to generate safe private keys, use the -s option to enter your passphrase which will be used for generating a base key as for BIP38 standard (*VanitySearch.exe -s "My PassPhrase" FXPref*). You can also use *VanitySearch.exe -ps "My PassPhrase"* which will add a crypto secure seed to your passphrase.\
VanitySearch may not compute a good grid size for your GPU, so try different values using -g option in order to get the best performances. If you want to use GPUs and CPUs together, you may have best performances by keeping one CPU core for handling GPU(s)/CPU exchanges (use -t option to set the number of CPU threads).

# Feature

<ul>
  <li>Fixed size arithmetic</li>
  <li>Fast Modular Inversion (Delayed Right Shift 62 bits)</li>
  <li>SecpK1 Fast modular multiplication (2 steps folding 512bits to 256bits using 64 bits digits)</li>
  <li>Use some properties of elliptic curve to generate more keys</li>
  <li>SSE Secure Hash Algorithm SHA256 and RIPEMD160 (CPU)</li>
  <li>Multi-GPU support</li>
  <li>CUDA optimisation via inline PTX assembly</li>
  <li>Seed protected by pbkdf2_hmac_sha512 (BIP38)</li>
  <li>Support P2PKH, P2SH and BECH32 addresses</li>
  <li>Support split-key vanity address</li>
</ul>

# Usage

You can download latest release from https://github.com/Groestlcoin/VanitySearch/releases

```
VanitySearch [-check] [-v] [-u] [-b] [-c] [-gpu] [-stop] [-i inputfile]
             [-gpuId gpuId1[,gpuId2,...]] [-g g1x,g1y,[,g2x,g2y,...]]
             [-o outputfile] [-m maxFound] [-ps seed] [-s seed] [-t nbThread]
             [-nosse] [-r rekey] [-check] [-kp] [-sp startPubKey]
             [-rp privkey partialkeyfile] [prefix]

 prefix: prefix to search (Can contains wildcard '?' or '*')
 -v: Print version
 -u: Search uncompressed addresses
 -b: Search both uncompressed or compressed addresses
 -c: Case unsensitive search
 -gpu: Enable gpu calculation
 -stop: Stop when all prefixes are found
 -i inputfile: Get list of prefixes to search from specified file
 -o outputfile: Output results to the specified file
 -gpu gpuId1,gpuId2,...: List of GPU(s) to use, default is 0
 -g g1x,g1y,g2x,g2y, ...: Specify GPU(s) kernel gridsize, default is 8*(MP number),128
 -m: Specify maximun number of prefixes found by each kernel call
 -s seed: Specify a seed for the base key, default is random
 -ps seed: Specify a seed concatened with a crypto secure random seed
 -t threadNumber: Specify number of CPU thread, default is number of core
 -nosse: Disable SSE hash function
 -l: List cuda enabled devices
 -check: Check CPU and GPU kernel vs CPU
 -cp privKey: Compute public key (privKey in hex hormat)
 -kp: Generate key pair
 -rp privkey partialkeyfile: Reconstruct final private key(s) from partial key(s) info.
 -sp startPubKey: Start the search with a pubKey (for private key splitting)
 -r rekey: Rekey interval in MegaKey, default is disabled
```
# Wildcards

Supported wildcard characters include:
`?` - any one character
`*` - any number of characters

Considerations:
1. a pattern such as `Ftest` is the same as `Ftest*`
2. `F?test` will generate no matches, but `F?test*` will. If `?` is used, then other wildcards must be used to match a 35 character address (for legacy addresses).
3. `F?t*` is the same as`F?t???????????????????????????????`

Example (Windows, Intel(R) Core(TM) i9-9980HK 2.4GHz 16 multithreaded cores, GeForce RTX 2080):
```
C:\Users\Jackie\Desktop\VanitySearch.exe -stop -gpu FXTryMe
VanitySearch v1.16
Difficulty: 15318045009
Search: FXTryMe [Compressed]
Start Fri Jan 17 08:52:52 2020
Base Key: 14B39C627099FCACE9A36C13910F2F3BB82BBDC2307230933364C092D2692966
Number of CPU thread: 15
GPU: GPU #0 GeForce RTX 2080 (46x64 cores) Grid(368x128)
[1413.49 Mkey/s][GPU 1368.35 Mkey/s][Total 2^34.01][Prob 67.8%][70% in 00:00:00][Found 0]
Pub Addr: FXTryMemTGSHNw6BQJkWQ7385oZU7xGqKz
Priv (WIF): p2pkh:KxZMSw7tcbdkUcggrhfDHsfYrGFU4QUeNf7jh6XRLk55G7Q41o5f
Priv (HEX): 0x27F135DC443F74D8C80DD749358F481DA0C96921802BEBE6C5B7D4FBCB8D278C
```

```
C:\Users\Jackie\Desktop\VanitySearch.exe -stop -gpu 3MyCoin
VanitySearch v1.16
Difficulty: 15318045009
Search: 3MyCoin [Compressed]
Start Fri Jan 17 08:54:36 2020
Base Key: 7382A0C7A82F7E73FD50FFC939F8C137AE4EDCA155B0EB48DAB7A5FCFF887753
Number of CPU thread: 15
GPU: GPU #0 GeForce RTX 2080 (46x64 cores) Grid(368x128)
[815.47 Mkey/s][GPU 796.55 Mkey/s][Total 2^34.89][Prob 87.4%][90% in 00:00:04][Found 0]
Pub Addr: 3MyCoincPzBHyK8aM1QX6dgKhBEBcA2LPa
Priv (WIF): p2wpkh-p2sh:KzjAzfGSBkUFGRaPzXd7bewaxaoUGaMrGqnNzM7XAZh69KYU4oZa
Priv (HEX): 0x68AB2F01498B7B826E52E7AE87B5583C7238288578F6C8A3A4F93E6A018EC08A
```

```
C:\Users\Jackie\Desktop\VanitySearch.exe -stop -gpu grs1quantum
VanitySearch v1.16
Difficulty: 34359738368
Search: grs1quantum [Compressed]
Start Fri Jan 17 08:55:41 2020
Base Key: 97E95720592A4C8370943BA6EDDE58777DDAEBC7868AF74A9D953A07E159CDD5
Number of CPU thread: 15
GPU: GPU #0 GeForce RTX 2080 (46x64 cores) Grid(368x128)

Pub Addr: grs1quantummzkczqvtshflzaq070azl43s7cuzz06f
Priv (WIF): p2wpkh:L5fivFHygeeGSQFiJVxR5j6e7jn9ZtDwB6caP6TJGfctCLtvgS6j
Priv (HEX): 0xFC14C106F47022CB56A965F993D6725FE84029751A7A9394350F0B3676D2197B
```

# Impossible second character prefixes for F address

F1
F2
F3
F4
F5
F6
F7
F8
F9
Fw
Fy
Fu
FU
FP
FA
FS
FD
FF
FG
FH
FJ
FK
FL
Fz
Fx
FC
Fv
FV
FB
FN
FM

# Possible prefixes for 3 address
31h2 to 3R2c only

# Generate a vanity address for a third party using split-key

It is possible to generate a vanity address for a third party in a safe manner using split-key.\
For instance, Alice wants a nice prefix but does not have CPU power. Bob has the requested CPU power but cannot know the private key of Alice, Alice has to use a split-key.

## Step 1

Alice generates a key pair on her computer then send the generated public key and the wanted prefix to Bob. It can be done by email, nothing is secret.  Nevertheless, Alice has to keep safely the private key and not expose it.
```
VanitySearch.exe -s "AliceSeed" -kp
Priv : L4U2Ca2wyo721n7j9nXM9oUWLzCj19nKtLeJuTXZP3AohWBGuT7L
Pub  : 03FC71AE1E88F143E8B05326FC9A83F4DAB93EA88FFEACD37465ED843FCC75AA81
```
Note: The key pair is a standard SecpK1 key pair and can be generated with a third party software.

## Step 2

Bob runs VanitySearch using the Alice's public key and the wanted prefix.
```
VanitySearch.exe -sp 03FC71AE1E88F143E8B05326FC9A83F4DAB93EA88FFEACD37465ED843FCC75AA81 -gpu -stop -o keyinfo.txt FaLice
```
It generates a keyinfo.txt file containing the partial private key.
```
Pub Addr: FaLicewbpgYszGJYWDLUWXGwRy5f5k8YdJ
PartialPriv: KymTfgpgUez975zdJ6WApJ3vh95icvN7HMNQT14jfszTyNM7puen
```
Bob sends back this file to Alice. It can also be done by email. The partial private key does not allow anyone to guess the final Alice's private key.

## Step 3

Alice can then reconstructs the final private key using her private key (the one generated in step 1) and the keyinfo.txt from Bob.

```
VanitySearch.exe -rp L4U2Ca2wyo721n7j9nXM9oUWLzCj19nKtLeJuTXZP3AohWBGuT7L keyinfo.txt

Pub Addr: FaLicewbpgYszGJYWDLUWXGwRy5f5k8YdJ
Priv (WIF): p2pkh:L4R2zNta9Y16UYsSUCvDRQBdM1qezNjmC1sUyyZbS6jpFffAYmoJ
Priv (HEX): 0xD6AFF8D392C2FDBE7C34FD78204C100AC31D570954C8C879CAB5A4C04E15CCF5
```

## How it works

Basically the -sp (start public key) adds the specified starting public key (let's call it Q) to the starting keys of each threads. That means that when you search (using -sp), you do not search for addr(k.G) but for addr(k<sub>part</sub>.G+Q) where k is the private key in the first case and k<sub>part</sub> the "partial private key" in the second case. G is the SecpK1 generator point.\
Then the requester can reconstruct the final private key by doing k<sub>part</sub>+k<sub>secret</sub> (mod n) where k<sub>part</sub> is the partial private key found by the searcher and k<sub>secret</sub> is the private key of Q (Q=k<sub>secret</sub>.G). This is the purpose of the -rp option.\
The searcher has found a match for addr(k<sub>part</sub>.G+k<sub>secret</sub>.G) without knowing k<sub>secret</sub> so the requester has the wanted address addr(k<sub>part</sub>.G+Q) and the corresponding private key k<sub>part</sub>+k<sub>secret</sub> (mod n). The searcher is not able to guess this final private key because he doesn't know k<sub>secret</sub> (he knows only Q).

Note: This explanation is simplified, it does not take care of symmetry and endomorphism optimizations but the idea is the same.

# Trying to attack a list of addresses

The groestlcoin address (P2PKH) consists of a hash160 (displayed in Base58 format) which means that there are 2<sup>160</sup> possible addresses. A secure hash function can be seen as a pseudo number generator, it transforms a given message in a random number. In this case, a number (uniformaly distributed) in the range [0,2<sup>160</sup>]. So, the probability to hit a particular number after n tries is 1-(1-1/2<sup>160</sup>)<sup>n</sup>. We perform n Bernoulli trials statistically independent.\
If we have a list of m distinct addresses (m<=2<sup>160</sup>), the search space is then reduced to 2<sup>160</sup>/m, the probability to find a collision after 1 try becomes m/2<sup>160</sup> and the probability to find a collision after n tries becomes 1-(1-m/2<sup>160</sup>)<sup>n</sup>.\
An example:\
We have a hardware capable of generating **1GKey/s** and we have an input list of **10<sup>6</sup>** addresses, the following table shows the probability of finding a collision after a certain amount of time:

| Time     |  Probability  |
|----------|:-------------:|
| 1 second |6.8e-34|
| 1 minute |4e-32|
| 1 hour |2.4e-30|
| 1 day |5.9e-29|
| 1 year |2.1e-26|
| 10 years | 2.1e-25 |
| 1000 years | 2.1e-23 |
| Age of earth | 8.64e-17 |
| Age of universe | 2.8e-16 (much less than winning at the lottery) |

Calculation has been done using this [online high precision calculator](https://keisan.casio.com/calculator)

As you can see, even with a competitive hardware, it is very unlikely that you find a collision. Birthday paradox doesn't apply in this context, it works only if we know already the public key (not the address, the hash of the public key) we want to find.  This program doesn't look for collisions between public keys. It searchs only for collisions with addresses with a certain prefix.

# Compilation

## Windows

Intall CUDA SDK and open VanitySearch.sln in Visual C++ 2017.\
You may need to reset your *Windows SDK version* in project properties.\
In Build->Configuration Manager, select the *Release* configuration.\
Build and enjoy.\
\
Note: The current release has been compiled with CUDA SDK 10.0, if you have a different release of the CUDA SDK, you may need to update CUDA SDK paths in VanitySearch.vcxproj using a text editor. The current nvcc option are set up to architecture starting at 3.0 capability, for older hardware, add the desired compute capabilities to the list in GPUEngine.cu properties, CUDA C/C++, Device, Code Generation.

## Linux

 - Intall CUDA SDK.
 - Install older g++ (just for the CUDA SDK). Depenging on the CUDA SDK version and on your Linux distribution you may need to install an older g++.
 - Install recent gcc. VanitySearch needs to be compiled and linked with a recent gcc (>=7). The current release has been compiled with gcc 7.3.0.
 - Edit the makefile and set up the appropriate CUDA SDK and compiler paths for nvcc. Or pass them as variables to `make` invocation.

    ```make
    CUDA       = /usr/local/cuda-8.0
    CXXCUDA    = /usr/bin/g++-4.8
    ```

 - You can enter a list of architectrures (refer to nvcc documentation) if you have several GPU with different architecture.

 - Set CCAP to the desired compute capability according to your hardware. See docker section for more. Compute capability 2.0 (Fermi) is deprecated for recent CUDA SDK.

 - Go to the VanitySearch directory.
 - To build CPU-only version (without CUDA support):
    ```sh
    $ make all
    ```
 - To build with CUDA:
    ```sh
    $ make gpu=1 CCAP=2.0 all
    ```

Runnig VanitySearch (Intel(R) Xeon(R) CPU, 8 cores,  @ 2.93GHz, Quadro 600 (x2))
```sh
$ export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64
$ ./VanitySearch -t 7 -gpu -gpuId 0,1 1TryMe
# VanitySearch v1.10
# Difficulty: 15318045009
# Search: 1TryMe [Compressed]
# Start Wed Mar 27 10:26:43 2019
# Base Key:C6718D8E50C1A5877DE3E52021C116F7598826873C61496BDB7CAD668CE3DCE5
# Number of CPU thread: 7
# GPU: GPU #1 Quadro 600 (2x48 cores) Grid(16x128)
# GPU: GPU #0 Quadro 600 (2x48 cores) Grid(16x128)
# 40.284 MK/s (GPU 27.520 MK/s) (2^31.84) [P 22.24%][50.00% in 00:02:47][0]
#
# Pub Addr: 1TryMeERTZK7RCTemSJB5SNb2WcKSx45p
# Priv (WIF): Ky9bMLDpb9o5rBwHtLaidREyA6NzLFkWJ19QjPDe2XDYJdmdUsRk
# Priv (HEX): 0x398E7271AF3E5A78821C1ADFDE3EE90760A6B65F72D856CFE455B1264350BCE8
```

## Docker

[![Docker Stars](https://img.shields.io/docker/stars/ratijas/vanitysearch.svg)](https://hub.docker.com/r/ratijas/vanitysearch)
[![Docker Pulls](https://img.shields.io/docker/pulls/ratijas/vanitysearch.svg)](https://hub.docker.com/r/ratijas/vanitysearch)

### Supported tags

 * [`latest`, `cuda-ccap-6`, `cuda-ccap-6.0` *(cuda/Dockerfile)*](./docker/cuda/Dockerfile)
 * [`cuda-ccap-5`, `cuda-ccap-5.2` *(cuda/Dockerfile)*](./docker/cuda/Dockerfile)
 * [`cuda-ccap-2`, `cuda-ccap-2.0` *(cuda/ccap-2.0.Dockerfile)*](./docker/cuda/ccap-2.0.Dockerfile)
 * [`cpu` *(cpu/Dockerfile)*](./docker/cpu/Dockerfile)

### Docker build

Docker images are build for CPU-only version and for each supported CUDA Compute capability version (`CCAP`). Generally, users should choose latest `CCAP` supported by their hardware and driver. Compatibility table can be found on [Wikipedia](https://en.wikipedia.org/wiki/CUDA#GPUs_supported) or at the official NVIDIA web page of your product.

Docker uses multi-stage builds to improve final image size. Scripts are provided to facilitate the build process.

When building on your own, full image name (including owner/repo parts) can be customized via `IMAGE_NAME` environment variable. It defaults to just `vanitysearch` withour owner part. Pre-built images are available on Docker hub from [@ratijas](https://hub.docker.com/r/ratijas/vanitysearch).

#### Docker build / CPU-only

Build and tag `vanitysearch:cpu` image:
```sh
$ ./docker/cpu/build.sh
```

#### Docker build / GPU

Build with "default" GPU support, which might not be suitable for your system:
```sh
$ ./docker/cuda/build.sh
```

Build with customized GPU support:
```sh
$ env CCAP=5.2 CUDA=10.2 ./docker/cuda/build.sh
```

As for docker-compose folks, sorry, docker-composed GPUs are not (yet) supported on a 3.x branch. But it (hopefully) will change soon.

### Docker run

Note: VanitySearch image does not (neither should) require network access. To further ensure no data ever leaks from the running container, always pass `--network none` to the docker run command.

```sh
$ docker run -it --rm --gpus all --network none ratijas/vanitysearch:cuda-ccap-5.2 -gpu -c -stop 1docker
# VanitySearch v1.18
# Difficulty: 957377813
# Search: 1docker [Compressed, Case unsensitive] (Lookup size 3)
# Start Sat Jul 11 17:41:32 2020
# Base Key: B506F2C7CA8AA2E826F2947012CFF15D2E6CD3DA5C562E8252C9F755F2A4C5D3
# Number of CPU thread: 1
# GPU: GPU #0 GeForce GTX 970M (10x128 cores) Grid(80x128)
#
# PubAddress: 1DoCKeRXYyydeQy6xxpneqtDovXFarAwrE
# Priv (WIF): p2pkh:KzESATCZFmnH1RfwT5XbCF9dZSnDGTS8z61YjnQbgFiM7tXtcH73
# Priv (HEX): 0x59E27084C6252377A8B7AABB20AFD975060914B3747BD6392930BC5BE7A06565
```

# License

VanitySearch is licensed under GPLv3.
