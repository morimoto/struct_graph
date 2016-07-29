/*
 * sample.c
 *
 * Copyright (c) 2016 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 *
 * This sample came from Linux Kernel ALSA SoC code
 */

struct snd_soc_dai_link {
  const char *cpu_name;
  struct device_node *cpu_of_node, *codec_of_node;

  const char *cpu_dai_name,  *codec_name, *codec_dai_name;
};

struct device_node {
};

struct snd_soc_codec {
  struct snd_soc_component component;
};

struct snd_soc_platform {
  struct snd_soc_component component;
};

struct snd_soc_dai {
  struct snd_soc_codec *codec;
  struct snd_soc_component *component;
};

struct snd_pcm_substream {
  struct snd_pcm_runtime *runtime;
  struct snd_soc_pcm_runtime *private_data;		/* copied from pcm->private_data */
};

struct snd_pcm_runtime {
  struct snd_pcm_substream *trigger_master;

};

struct snd_soc_card {
  /* CPU <--> Codec DAI links  */
  struct snd_soc_dai_link *dai_link;	/* original was list_head */

  struct snd_soc_pcm_runtime *rtd_list;
};

struct snd_soc_pcm_runtime {
  struct snd_soc_card *card;
  struct snd_soc_dai_link *dai_link;

  /* runtime devices */
  struct snd_soc_codec *codec;
  struct snd_soc_platform *platform;
  struct snd_soc_dai *codec_dai, *cpu_dai, **codec_dais;
};

struct snd_soc_component {
  //  struct snd_soc_card *card;
  struct snd_soc_pcm_runtime *rtd;
  void *codec(snd_soc_codec);
  struct snd_soc_dai *dai_list; /* originail was list_head */
};
