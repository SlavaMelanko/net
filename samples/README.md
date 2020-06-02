# Net Samples

All samples must be located in `net/build/bin` directory.

## Client/Server pattern (using Dealer/Router sockets)

```bash
./server-sample -p 5555
./client-sample -i test -p 5555
```

In order to analyze protocol more detailed use [Wireshark](https://www.wireshark.org/), for example for localhost setup (macOS)

- Select [virtual loopback interface](https://wiki.wireshark.org/CaptureSetup/Loopback) from capturing list.
More specifically name must be `Loopback: loO`.
- And then apply a display filter, for instance `tcp.port == 5555`.

## Publish/Subscribe pattern (using Pub/Sub sockets)

```bash
./publisher-sample -p 5555
./subscriber-sample -p 5555
```

## Client/Server pattern with Broker

```bash
./broker-sample -f 5559 -b 5560
./worker-sample -p 5560
./client-sample -i test1 -p 5559
```

> TODO: img

## Advanced

```bash
./service-sample -s 5555 -p 5556
./agent-sample -i test -s 5555 -p 5556
```

> TODO: img
