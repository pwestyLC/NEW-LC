// Decompiled with JetBrains decompiler
// Type: MyNetworkStream
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Net.Sockets;

#nullable disable
internal class MyNetworkStream : NetworkStream
{
  private const int MaxRetryCount = 2;
  private Socket socket;

  public MyNetworkStream(Socket socket, bool ownsSocket)
    : base(socket, ownsSocket)
  {
    this.socket = socket;
  }

  private bool IsTimeoutException(SocketException e) => e.SocketErrorCode == SocketError.TimedOut;

  private bool IsWouldBlockException(SocketException e)
  {
    return e.SocketErrorCode == SocketError.WouldBlock;
  }

  private void HandleOrRethrowException(Exception e)
  {
    for (Exception exception = e; exception != null; exception = exception.InnerException)
    {
      if (exception is SocketException)
      {
        SocketException e1 = (SocketException) exception;
        if (this.IsWouldBlockException(e1))
        {
          this.socket.Blocking = true;
          return;
        }
        if (this.IsTimeoutException(e1))
          throw new TimeoutException(e1.Message, e);
      }
    }
    throw e;
  }

  public override int Read(byte[] buffer, int offset, int count)
  {
    int num = 0;
    Exception exception;
    do
    {
      try
      {
        return base.Read(buffer, offset, count);
      }
      catch (Exception ex)
      {
        exception = ex;
        this.HandleOrRethrowException(ex);
      }
    }
    while (++num < 2);
    throw exception;
  }

  public override int ReadByte()
  {
    int num = 0;
    Exception exception;
    do
    {
      try
      {
        return base.ReadByte();
      }
      catch (Exception ex)
      {
        exception = ex;
        this.HandleOrRethrowException(ex);
      }
    }
    while (++num < 2);
    throw exception;
  }

  public override void Write(byte[] buffer, int offset, int count)
  {
    int num = 0;
    Exception exception;
    do
    {
      try
      {
        base.Write(buffer, offset, count);
        return;
      }
      catch (Exception ex)
      {
        exception = ex;
        this.HandleOrRethrowException(ex);
      }
    }
    while (++num < 2);
    throw exception;
  }

  public override void Flush()
  {
    int num = 0;
    Exception exception;
    do
    {
      try
      {
        base.Flush();
        return;
      }
      catch (Exception ex)
      {
        exception = ex;
        this.HandleOrRethrowException(ex);
      }
    }
    while (++num < 2);
    throw exception;
  }
}
